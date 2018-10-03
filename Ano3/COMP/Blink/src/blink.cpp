#include <Arduino.h>

enum {
    LED = 13,
};

#if 0
void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    digitalWrite(LED, true);
    delay(1000);
    digitalWrite(LED, false);
    delay(1000);
}
#else
void setup() {
    TRISFCLR = 0x0001;
}

void loop() {
    LATFINV = 0x0001;
    delay(1000);
}
#endif
