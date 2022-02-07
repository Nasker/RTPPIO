#include "RTPMainUnit.hpp"
#include "ControlCommand.h"

RTPMainUnit::RTPMainUnit(){
}

void RTPMainUnit::begin(){  
  Serial.begin(115200);
  Wire.begin();
  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
  rtpTrellis.begin(this);
  outDevicesManager.initSetup();
  outDevicesManager.connectNeoTrellis(rtpTrellis);
  stateMachineManager.connectOutDevices(outDevicesManager);
  stateMachineManager.connectSequencer(Sequencer);
	SequencerManager.connectSequencer(Sequencer);
  outDevicesManager.printToScreen("Hey there!", "I'm Buit!", "FTW!");
}

void RTPMainUnit::update(){
  rtpRotary.callbackFromRotary(this);
  rtpRotary.callbackFromClicks(this);
  vlSensor.callbackThreeAxisChanged(this);
  rtpTrellis.read();
}

void RTPMainUnit::actOnControlsCallback(ControlCommand callbackCommand){
  //outDevicesManager.printToScreen(callbackCommand);
  stateMachineManager.handleActions(callbackCommand);
}

void RTPMainUnit::linkToSequencerManager(byte realtimebyte){
  SequencerManager.handleRealTimeSystem(realtimebyte);
}