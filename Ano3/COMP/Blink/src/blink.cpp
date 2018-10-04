#include <Arduino.h>

enum {
    LED = 13,
    DELAY = 250,
};

#if 1

void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    digitalWrite(LED, true);
    delay(DELAY);
    digitalWrite(LED, false);
    delay(DELAY);
}

#else

void setup() {
    TRISFCLR = 0x0001;
}

void loop() {
    LATFINV = 0x0001;
    delay(DELAY);
}

#endif
