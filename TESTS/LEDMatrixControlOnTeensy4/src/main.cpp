#include <Arduino.h>
#include "Ticker.h"
#include "Adafruit_GFX.h"

#define TICKER_PERIOD 100

bool state = false;

void blink() {
  digitalWrite(LED_BUILTIN, state);
  state = !state;
}

Ticker ticker(blink, TICKER_PERIOD, 0, MILLIS);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  ticker.start();
}

void loop() {
  ticker.update();
}
