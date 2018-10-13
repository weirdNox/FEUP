#include <Arduino.h>
#include <OneButton.h>

#define LED4 13
#define LED 7
#define BUT 6

OneButton button(BUT, true);
// includes pinMode on BUT

void callback() {
  static int LEDstate = LOW;

  digitalWrite(LED, LEDstate = !LEDstate);
}

bool LED4state = false;
unsigned long last;

void setup() {
  pinMode(LED4, OUTPUT);
  digitalWrite(LED4, LOW);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  button.attachClick(callback);

  last = millis();
}

void loop() {
  if (millis() - last > 1000) {
    digitalWrite(LED4, LED4state = !LED4state);
    last += 1000;
  }

  button.tick();
}
