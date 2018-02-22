/////////////////////////////////////////////////
// Sistemas e Automação                        //
// (C) FEUP paco@fe.up.pt and asousa@fe.up.pt  //
/////////////////////////////////////////////////

#include "sa.h"


// Define 8 global timers
const int total_timers  = 8;
timer_t timer[total_timers];

// To be updated by read_inputs at start of cycle - do not touch
byte sens_in;
byte sens_out;

// To be updated by write_outputs at end of cycle - do not touch
byte sign_red;
byte sign_green;
byte barr_in;
byte barr_out;

// Input PINs =====> Rectify with your own pins if needed
const int pin_sens_in   = 9;
const int pin_sens_out  = 8;

// OUTPUT PINs =====> Rectify with your own pins if needed
const int pin_green    = 5;
const int pin_red      = 4;
const int pin_barr_in  = 3;
const int pin_barr_out = 2;

// Run Once After Reset or PowerUp (to setup hardware, etc)
void setup()
{
  // Serial Port Speed
  Serial.begin(115200);

  // Init message
  Serial.println("(C)FEUP S&A - start init");


  // Define Input and Output Pins
  pinMode(pin_green, OUTPUT);
  pinMode(pin_red, OUTPUT);
  pinMode(pin_barr_in, OUTPUT);
  pinMode(pin_barr_out, OUTPUT);
  pinMode(pin_sens_in, INPUT_PULLUP);
  pinMode(pin_sens_out, INPUT_PULLUP);

  digitalWrite(pin_green, HIGH);    delay(500);    // Leds one at a time
  digitalWrite(pin_red, HIGH);      delay(500);    // Leds one at a time
  digitalWrite(pin_barr_in, HIGH);  delay(500);    // Leds one at a time
  digitalWrite(pin_barr_out, HIGH); delay(500);    // Leds one at a time

  // Setup Timers
  timer[0].p = 20; // 2 seconds
  start_timer(timer[0]);
  timer[1].p = 5; // 0.5 seconds
  start_timer(timer[1]);


  digitalWrite(pin_green, LOW);
  digitalWrite(pin_red, LOW);
  digitalWrite(pin_barr_in, LOW);
  digitalWrite(pin_barr_out, LOW);


  Serial.println("Init Done...");
} // End of Setup






// Update timers at start of cycle - do not touch
void refresh_timers(void)
{
 byte i;
 for(i = 0; i < total_timers; i++)
   refresh_timer(timer[i]);
} // End of refresh_timers()


// Read from pins to positive “Image_Variables” - do not touch
void read_inputs(void)
{
  if (digitalRead(pin_sens_in )==LOW) sens_in  = 1; else sens_in  = 0;
  if (digitalRead(pin_sens_out)==LOW) sens_out = 1; else sens_out = 0;
} // End of read_inputs()



// Write to pins from “Image_Variables” - do not touch
void write_outputs(void)
{
  digitalWrite(pin_green, sign_green);
  digitalWrite(pin_red, sign_red);
  digitalWrite(pin_barr_in, barr_in);
  digitalWrite(pin_barr_out, barr_out);
} // End of write_inputs



// Global Variables for Shield and S&A stuff - do not touch
long previousMicros = 0;

// Arduino Loop - do not touch
void loop()
{
  unsigned long currentMicros = micros();
  if(currentMicros - previousMicros > 10000) {   // 10 ms

    previousMicros = currentMicros;

    refresh_timers();
    read_inputs();

    loop_10ms();

    write_outputs();
  }
} // End of Arduino loop



///////////////////////////////////////////////////
///////                                     ///////
///////   Write Your Code below this line   ///////
///////                                     ///////
///////////////////////////////////////////////////



// Global Variables, define additional global vars below
byte state1 = 0;
byte state2 = 0;

// Loop where you should write your state machine code, etc
void loop_10ms(void)
{
  // Don't forget to comment or delete example code
  // Don't read nor write directly hardware pins

  // Example System of State machines with 2 independent state machines

  // Example StateMachine1 - StateVar => state1
    if ((state1 == 0) && (sens_out)) {
    state1 = 1;
    start_timer(timer[0]);
  } else if ((state1 == 1) && timer[0].q) {
    state1 = 0;
  } // end of calculation of next state for state1

  // Example StateMachine2 - StateVar => state2
  if ((state2 == 0) && (sens_in)) {
    state2 = 1;
    start_timer(timer[1]);
  } else if ((state2 == 1) && timer[1].q) {
    state2 = 0;
  } // end of calculation of next state for state2


  // Calculate Outputs
  sign_red   = (state1 == 0);
  sign_green = (state1 == 1);
  barr_in    = (state2 == 0);
  barr_out   = (state2 == 1);

  // Debug – print states and variables, change as you wish!
  Serial.println( "St1:"   + ((String) state1)    + "St2:"    + ((String) state2) +
                  " Sens:" + ((String) sens_in  ) + ((String) sens_out ) +
                  " Sign:" + ((String) sign_green) + ((String) sign_red) +
                  " Barr:" + ((String) barr_in)   + ((String) barr_out));

} // End of loop_10ms


