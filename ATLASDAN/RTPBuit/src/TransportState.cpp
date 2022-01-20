#include "Arduino.h"
#include "TransportState.h"

TransportState::TransportState (BuitStateMachine* buitMachine){
  Serial.println("TransportState");
  _buitMachine = buitMachine;
}

void TransportState::singleClick() {
  Serial.println("Does nothing here!");
}

void TransportState::doubleClick() {
  Serial.println("Going to Scene Edit!");
  _outDevices->printToScreen("State:", "Scene Edit!","");
  _buitMachine->setState(_buitMachine->getSceneEditState());
}

void TransportState::longClick() {
  Serial.println("Going to Global Settings!");
  _outDevices->printToScreen("State:", "Global Settings!","");
  _buitMachine->setState(_buitMachine->getGlobalSettingsState());
}

void TransportState::rotaryTurned(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void TransportState::threeAxisChanged(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void TransportState::trellisPressed(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void TransportState::trellisReleased(ControlCommand command) {
  Serial.println("Does nothing here!");
}  