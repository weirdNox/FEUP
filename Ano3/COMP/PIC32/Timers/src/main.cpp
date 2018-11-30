#include <Arduino.h>
#include <timer.cpp>

enum {
    Led = 13,
    InterruptPin = 38,
};

Timer4 Timer;

int Count = 0;
bool PrintMessage = true;

void count() {
    ++Count;
    PrintMessage = true;
}

void __attribute__((interrupt)) isrTimer() {
    static uint8_t State = LOW;
    static int C = 0;

    if(++C == 10) {
        State = !State;
        digitalWrite(Led, State);
        C = 0;
    }

    clearIntFlag(_TIMER_4_IRQ);
}

void setup() {
    Serial.begin(115200);

    pinMode(InterruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(InterruptPin), count, FALLING);

    pinMode(Led, OUTPUT);
    Timer.setFrequency(10);
    Timer.attachInterrupt(isrTimer);
    Timer.start();
}

void loop() {
    if(PrintMessage) {
        PrintMessage = false;
        Serial.println(Count);
    }
}
