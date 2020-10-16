#include "Arduino.h"
#include "RTPMainUnit.hpp"
#include "RTPPeriodicBang.h"


#define UPDATE_PERIOD 20

RTPMainUnit mUnit;
RTPPeriodicBang periodicUpdate(UPDATE_PERIOD);

void actOnPeriodicUpdate(String callbackString){
  mUnit.updatePeriodically();
}

void setup() {
  mUnit.begin();
}

void loop() {
  mUnit.update();
  periodicUpdate.callbackPeriodBang(actOnPeriodicUpdate);
}
