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
    timer[0].p = 40; // 4 seconds
    start_timer(timer[0]);
    timer[1].p = 40; // 4 seconds
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

const int capacity = 4;
int occupied_spaces = 0;
byte barrier_in_state = 0;
byte barrier_out_state = 0;
byte traffic_light_state = 0;

void loop_10ms(void)
{
    // Entrance barrier
    if(barrier_in_state == 0 && sens_in && occupied_spaces < capacity)
    {
        start_timer(timer[0]);
        barrier_in_state = 1;
        occupied_spaces++;
    }
    else if (barrier_in_state == 1 && !sens_in && timer[0].q)
    {
        barrier_in_state = 0;
    }

    // Out Barrier
    if(barrier_out_state == 0 && sens_out)
    {
        start_timer(timer[1]);
        barrier_out_state = 1;
        occupied_spaces = max(0, occupied_spaces-1);
    }
    else if (barrier_out_state == 1 && !sens_out && timer[1].q)
    {
        barrier_out_state = 0;
    }

    // Traffic light
    if(traffic_light_state == 0 && occupied_spaces >= capacity)
    {
        traffic_light_state = 1;
    }
    else if(traffic_light_state == 1 && occupied_spaces < capacity)
    {
        traffic_light_state = 0;
    }

    barr_in = (barrier_in_state == 1);
    barr_out = (barrier_out_state == 1);
    sign_green = (traffic_light_state == 0);
    sign_red = (traffic_light_state == 1);
}
