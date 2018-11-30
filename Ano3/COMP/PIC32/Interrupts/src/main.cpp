#include <Arduino.h>

enum {
    InterruptPin = 38,
};

int Count;
bool PrintMessage;

void count() {
    ++Count;
    PrintMessage = true;
}

void setup() {
    Serial.begin(115200);
    for(int I = 0; I <= 41; ++I) {
        int IntN = digitalPinToInterrupt(I);
        if(IntN >= 0) {
            Serial.printf("Pin %d = INT%d\n\r", I, IntN);
        }
    }

    pinMode(InterruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(InterruptPin), count, RISING);
}

void loop() {
    if(PrintMessage) {
        PrintMessage = false;
        Serial.printf("Button pressed %d times\n\r", Count);
    }
}
