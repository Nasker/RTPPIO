#include <Arduino.h>
#include "RTPSequencer.h"
#include "RTPSequencerManager.hpp"

RTPSequencer Sequencer(1);
RTPSequencerManager SequencerManager;

void linkToSequencerManager(byte realtimebyte){
	SequencerManager.handleRealTimeSystem(realtimebyte);
}

void setup(){
	Serial.begin(115200);
	usbMIDI.setHandleRealTimeSystem(linkToSequencerManager);
	SequencerManager.connectSequencer(Sequencer);
}

void loop() {
	usbMIDI.read();
}
