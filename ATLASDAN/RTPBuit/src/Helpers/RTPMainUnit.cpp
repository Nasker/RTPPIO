#include "RTPMainUnit.hpp"
#include "RTPMusicController.h"
#include "ControlCommand.h"
#include "MIDI.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI2);

RTPMainUnit::RTPMainUnit(){
}

void RTPMainUnit::begin(){  
  Serial.begin(115200);
  Wire.begin();
  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
  chordionKeys.initSetup();
  rtpTrellis.begin(this);
  devicesManager.initSetup();
  devicesManager.connectNeoTrellis(rtpTrellis);
  devicesManager.connectSequencer(Sequencer);
  stateMachineManager.connectDevices(devicesManager);
	SequencerManager.connectSequencer(Sequencer);
  devicesManager.printToScreen("Hey there!", "I'm Buit!", "FTW!");
}

void RTPMainUnit::update(){
  rtpRotary.callbackFromRotary(this);
  rtpRotary.callbackFromClicks(this);
  vlSensor.callbackThreeAxisChanged(this);
  rtpTrellis.read();
}

void RTPMainUnit::actOnControlsCallback(ControlCommand callbackCommand){
  //devicesManager.printToScreen(callbackCommand);
  stateMachineManager.handleActions(callbackCommand);
}

void RTPMainUnit::linkToSequencerManager(byte realtimebyte){
  SequencerManager.handleRealTimeSystem(realtimebyte);
}