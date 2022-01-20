#include "Arduino.h"
#include "RTPMainUnit.hpp"

RTPMainUnit mUnit;

void setup() {
  mUnit.begin();
}

void loop() {
  mUnit.update();
}
