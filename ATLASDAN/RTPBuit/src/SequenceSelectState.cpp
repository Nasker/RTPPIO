#include "Arduino.h"

#include "SequenceSelectState.h"

SequenceSelectState::SequenceSelectState(BuitStateMachine* buitMachine){
  Serial.println("SequenceSelectState");
  _buitMachine = buitMachine;
}

void SequenceSelectState::singleClick() {
  Serial.println("Going to Sequence Edit!");
  _outDevices->printToScreen("State:", "Sequence Edit!","");
  _buitMachine->setState(_buitMachine->getSequenceEditState());
}


void SequenceSelectState::doubleClick() {
  Serial.println("Going to Scene Edit!");
  _outDevices->printToScreen("State:", "Scene Edit!","");
  _buitMachine->setState(_buitMachine->getSceneEditState());
}

void SequenceSelectState::longClick() {
  Serial.println("Does nothing here!");
}

void SequenceSelectState::rotaryTurned(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void SequenceSelectState::threeAxisChanged(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void SequenceSelectState::trellisPressed(ControlCommand command) {
  Serial.printf("Editing sequence #%d\n", command.value);
  _outDevices->printToScreen("Editing sequence", "", String(command.value));
  _buitMachine->setState(_buitMachine->getSequenceEditState());
}

void SequenceSelectState::trellisReleased(ControlCommand command) {
  Serial.println("Does nothing here!");
}