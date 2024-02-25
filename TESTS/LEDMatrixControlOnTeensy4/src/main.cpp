#include <Arduino.h>
#include "Ticker.h"

bool state = false;

void blink() {
  digitalWrite(LED_BUILTIN, state);
  state = !state;
}

Ticker ticker(blink, 500, 0, MILLIS);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  ticker.start();
}

void loop() {
  ticker.update();
}
