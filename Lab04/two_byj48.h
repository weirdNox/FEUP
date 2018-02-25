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

#pragma GCC optimize ("-O3")

#ifndef TWO_BYJ48_H
#define TWO_BYJ48_H

#include "Arduino.h"

#define M1_1 8 
#define M1_2 9 
#define M1_3 10 
#define M1_4 11

#define M1_PORT  PORTB
#define M1_SHIFT 0

#define M2_1 A2 
#define M2_2 A3
#define M2_3 A4
#define M2_4 A5

#define M2_PORT  PORTC
#define M2_SHIFT 2

#define DEBUG_PIN_NUM  12 // PB4 - Debug pin 
#define DEBUG_PIN  4 // PB4 - Debug pin 
#define DEBUG_PORT PORTB // PB4 - Debug pin 


#define ONE_STEP 10000
#define NUM_MOTORS 2
#define INT_RATE 10000

typedef struct{
    int sub_pos, speed, req_speed;
    byte accel;
    //byte pin_step, pin_dir;
} motor_t;

void two_byj48_init(void);
void set_motor_pos(byte mot, int new_pos);
int  get_motor_pos(byte mot);
void set_motor_speed(byte mot, int new_speed);
void set_motor_req_speed(byte mot, int new_speed);
int get_motor_req_speed(byte mot);
void set_motor_accel(byte mot, byte new_accel);

int get_motor_speed(byte mot);


#endif // TWO_BYJ48_H
