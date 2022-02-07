#include "Arduino.h"
#include "InitState.h"

InitState::InitState(BuitStateMachine* buitMachine){
  Serial.println("InitState");
  _buitMachine = buitMachine;
}

void InitState::singleClick() {
  Serial.println("Going to Transport");
  _devices->presentTransport();
  _buitMachine->setState(_buitMachine->getTransportState());
}

void InitState::doubleClick() {
  Serial.println("Going to Transport");
  _devices->presentTransport();
  _buitMachine->setState(_buitMachine->getTransportState());
}

void InitState::longClick() {
  Serial.println("Going to Transport");
  _devices->presentTransport();
  _buitMachine->setState(_buitMachine->getTransportState());
}

void InitState::rotaryTurned(ControlCommand command) {
    Serial.println("Going to Transport");
  _devices->presentTransport();
  _buitMachine->setState(_buitMachine->getTransportState());
}

void InitState::threeAxisChanged(ControlCommand command) {
  //Serial.println("Does nothing here!");
}

void InitState::trellisPressed(ControlCommand command) {
  Serial.println("Going to Transport");
  _devices->presentTransport();
  _buitMachine->setState(_buitMachine->getTransportState());
} 

void InitState::trellisReleased(ControlCommand command) {
  //Serial.println("Does nothing here!");
}