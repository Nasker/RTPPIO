#include "RTPMainUnit.hpp"
#include "RTPMusicController.h"
#include "ControlCommand.h"
#include "MIDI.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI2);

RTPMainUnit::RTPMainUnit(){
}

void linkToSequencerManager(byte realtimebyte){
	//SequencerManager.handleRealTimeSystem(realtimebyte);
  Serial.println(realtimebyte);
}

void RTPMainUnit::begin(){  
  Serial.begin(115200);
  Wire.begin();
  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
  chordionKeys.initSetup();
  rtpTrellis.begin(this);
  outDevicesManager.initSetup();
  outDevicesManager.connectNeoTrellis(rtpTrellis);
  stateMachineManager.connectOutDevices(outDevicesManager);
  usbMIDI.setHandleRealTimeSystem(linkToSequencerManager);
	SequencerManager.connectSequencer(Sequencer);
  outDevicesManager.printToScreen("Hey there!", "I'm Buit!", "FTW!");
}

void RTPMainUnit::update(){
  rtpRotary.callbackFromRotary(this);
  rtpRotary.callbackFromClicks(this);
  vlSensor.callbackThreeAxisChanged(this);
  rtpTrellis.read();
  usbMIDI.read();
}


void RTPMainUnit::actOnControlsCallback(ControlCommand callbackCommand){
  //outDevicesManager.printToScreen(callbackCommand);
  stateMachineManager.handleActions(callbackCommand);
}