#include "RTPMainUnit.hpp"
#include "ControlCommand.h"

RTPMainUnit::RTPMainUnit(){
}

void RTPMainUnit::begin(){  
  Serial.begin(9600);
  Wire.begin();
  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
  rtpTrellis.begin(this);
  devicesManager.initSetup();
  devicesManager.connectNeoTrellis(rtpTrellis);
  devicesManager.connectSequencer(Sequencer);
  devicesManager.connectMusicManager(musicManager);
  stateMachineManager.connectDevices(devicesManager);
	SequencerManager.connectSequencer(Sequencer);
  devicesManager.printToScreen("Hey there!", "I'm Buit!", "FTW!");
}

void RTPMainUnit::update(){
  rtpRotary.callbackFromRotary(this);
  rtpRotary.callbackFromClicks(this);
  rtpTrellis.read();
}

void RTPMainUnit::updatePeriodically(){
  vlSensor.callbackThreeAxisChanged(this);
}

void RTPMainUnit::actOnControlsCallback(ControlCommand callbackCommand){
  //devicesManager.printToScreen(callbackCommand);
  stateMachineManager.handleActions(callbackCommand);
}

void RTPMainUnit::linkToSequencerManager(byte realtimebyte){
  SequencerManager.handleRealTimeSystem(realtimebyte);
}

void RTPMainUnit::routeControlChange(byte channel, byte control, byte value) {
  //Serial.printf("Control change: %d %d %d\n", channel, control, value);
  musicManager.setCurrentHarmony(channel, control, value);
}