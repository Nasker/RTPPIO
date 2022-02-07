#include "Arduino.h"
#include "TransportState.h"

TransportState::TransportState (BuitStateMachine* buitMachine){
  Serial.println("TransportState");
  _buitMachine = buitMachine;
}

void TransportState::singleClick() {
}

void TransportState::doubleClick() {
  Serial.println("Going to Scene Edit!");
  _devices->presentScene();
  _buitMachine->setState(_buitMachine->getSceneEditState());
}

void TransportState::longClick() {
  Serial.println("Going to Global Settings!");
  _devices->printToScreen("Global Settings", "","");
  _buitMachine->setState(_buitMachine->getGlobalSettingsState());
}

void TransportState::rotaryTurned(ControlCommand command) {

}

void TransportState::threeAxisChanged(ControlCommand command) {

}

void TransportState::trellisPressed(ControlCommand command) {

}

void TransportState::trellisReleased(ControlCommand command) {

}  