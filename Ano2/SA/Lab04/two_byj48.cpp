/* Copyright (c) 2017  Paulo Costa
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
  
#include "Arduino.h"
#include "two_byj48.h"
#include <util/atomic.h>

#define BIT(x) (0x01 << (x))

byte toggle, even, adec;

motor_t motors[NUM_MOTORS];
volatile int motor_pos[NUM_MOTORS];
byte half_step_table[8] = {1, 1 + 2, 2, 2 + 4, 4, 4 + 8, 8, 8 + 1}; 
//byte half_step_table[8] = {1, 1 + 4, 4, 4 + 2, 2, 2 + 8, 8, 8 + 1}; 

// Attach interrupt routine to the Timer Compare Interrupt
ISR(TIMER2_COMPA_vect)
{
  DEBUG_PORT |= BIT(DEBUG_PIN);
  byte i, b;

  even++;
  if (even & 0x01) {

    // Acceleration effect on speed (for all motors)
    adec++;
    if (adec > 200) {
      adec = 0;
      for(i = 0; i < NUM_MOTORS; i++){

        // Speed must increase -> positive accceleration
        if (motors[i].req_speed > motors[i].speed) { 
          motors[i].speed += motors[i].accel;
          // But must stop on the req_speed value
          if (motors[i].speed > motors[i].req_speed) { 
            motors[i].speed = motors[i].req_speed;
          }  
       
        // Speed must decrease -> negative accceleration
        } else if (motors[i].req_speed < motors[i].speed) {
          motors[i].speed -= motors[i].accel;
          // But must stop on the req_speed value
          if (motors[i].speed < motors[i].req_speed) {
            motors[i].speed = motors[i].req_speed;
          }
        }
      }
    }
    // End or interrupt signal
    DEBUG_PORT &= ~BIT(DEBUG_PIN);
    return;
  }


  // Step if there is an underflow or a overflow
  // A step pulse will last 1/INT_RATE  (it must be > 1 us: A4988 datsheet)
  for(i = 0; i < NUM_MOTORS; i++){
    motors[i].sub_pos += motors[i].speed;
    if (motors[i].sub_pos > ONE_STEP) {
      motors[i].sub_pos -= ONE_STEP;
      motor_pos[i]++;
    } else if (motors[i].sub_pos < 0) {
      motors[i].sub_pos += ONE_STEP;
      motor_pos[i]--;
    }
  }

  // Update the stepper pins
  b = M1_PORT & ~(0b00001111 << M1_SHIFT);
  M1_PORT = b | (half_step_table[motor_pos[0] & 0x07] << M1_SHIFT);
  
  b = M2_PORT & ~(0b00001111 << M2_SHIFT);
  M2_PORT = b | (half_step_table[motor_pos[1] & 0x07] << M2_SHIFT);
   
  //digitalWrite(EN, 0);
  DEBUG_PORT &= ~BIT(DEBUG_PIN);
}

void set_motor_pos(byte mot, int new_pos)
{
  if (mot >= NUM_MOTORS) return;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    motor_pos[mot] = new_pos;
  }  
}

int get_motor_pos(byte mot)
{
  int result;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    result = motor_pos[mot];
  }  
  return result;
}



void set_motor_speed(byte mot, int new_speed)
{
  if (mot >= NUM_MOTORS) return;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    motors[mot].speed = new_speed;
  }  
}

int get_motor_speed(byte mot)
{
  int result;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    result = motors[mot].speed;
  }  
  return result;
}


void set_motor_req_speed(byte mot, int new_speed)
{
  if (mot >= NUM_MOTORS) return;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    motors[mot].req_speed = new_speed;
  }  
}

int get_motor_req_speed(byte mot)
{
  if (mot >= NUM_MOTORS) return 0;
  return motors[mot].req_speed;
}


void set_motor_accel(byte mot, byte new_accel)
{
  if (mot >= NUM_MOTORS) return;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    motors[mot].accel = new_accel;
  }  
}


void two_byj48_init(void)
{
  byte i;
  
  // Configure the steper drive pins as outputs
  pinMode(M1_1, OUTPUT); 
  pinMode(M1_2, OUTPUT); 
  pinMode(M1_3, OUTPUT); 
  pinMode(M1_4, OUTPUT); 

  pinMode(M2_1, OUTPUT); 
  pinMode(M2_2, OUTPUT); 
  pinMode(M2_3, OUTPUT); 
  pinMode(M2_4, OUTPUT); 
  
  pinMode(DEBUG_PIN_NUM, OUTPUT); 

  for (i = 0; i < NUM_MOTORS; i++) {
    motors[i].speed = 0;// * ONE_STEP / INT_RATE;
    motors[i].req_speed = 2000;
    motors[i].accel = 50;
  }

  
  // Disable interrupts
  uint8_t savedStatus = SREG;
  cli();
  // Use Timer2 with 50 (-100-) us interrupts
  // OC2A & OC2B disconnected, mode 7 (fast PWM, Clear Timer on Compare match)
  TCCR2A = BIT(WGM21) | BIT(WGM20);
  // Don't force output compare (FOCA & FOCB), mode 2, Clock Select clk/32 
  //TCCR2B = BIT(WGM22) | BIT(CS21) | BIT(CS20);
  // Don't force output compare (FOCA & FOCB), mode 2, Clock Select clk/8 
  TCCR2B = BIT(WGM22) | BIT(CS21);
  // Set timer counter compare match (when value reached, 100 us has elapsed)
  OCR2A = 200 - 1;
  // Set timer counter compare match (when value reached, 50 us has elapsed)
  //OCR2A = 100 - 1;
  // Reset Timer2 counter
  TCNT2 = 0;
  // Set Timer2 interrupt mode (Set interrupt on OCR2A compare match)
  TIMSK2 = BIT(OCIE2A);

  // Restore interrupt enabling state
  SREG = savedStatus; 

  for (i = 0; i < NUM_MOTORS; i++) {
    set_motor_req_speed(i, 0);
    set_motor_speed(i, 0);
  }

}
