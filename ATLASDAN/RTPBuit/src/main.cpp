#include "Arduino.h"
#include "RTPMainUnit.hpp"

RTPMainUnit mUnit;

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
}
