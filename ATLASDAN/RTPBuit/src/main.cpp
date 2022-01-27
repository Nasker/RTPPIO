#include "Arduino.h"
#include "RTPMainUnit.hpp"
#include "RTPPeriodicBang.h"

#define UPDATE_PERIOD 10

RTPMainUnit mUnit;
RTPPeriodicBang periodicUpdate(UPDATE_PERIOD);

void actOnPeriodicUpdate(String callbackString){
  mUnit.updatePeriodically();
}

void linkToSequencerManager(byte realtimebyte){
  mUnit.linkToSequencerManager(realtimebyte);
}

void setup() {
  mUnit.begin();
  usbMIDI.setHandleRealTimeSystem(linkToSequencerManager);
}

void loop() {
  usbMIDI.read();
  mUnit.update();
  periodicUpdate.callbackPeriodBang(actOnPeriodicUpdate);
}
