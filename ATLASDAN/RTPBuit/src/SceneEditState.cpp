#include "Arduino.h"

#include "SceneEditState.h"

SceneEditState::SceneEditState (BuitStateMachine* buitMachine){
  Serial.println("SceneEditState");
  _buitMachine = buitMachine;
}

void SceneEditState::singleClick() {
  Serial.println("Going to Sequence Select!");
  _outDevices->printToScreen("State:", "Sequence Select!","");
  _buitMachine->setState(_buitMachine->getSequenceSelectState());
}

void SceneEditState::doubleClick() {
  Serial.println("Going to Transport");
  _outDevices->printToScreen("State:", "Transport!","");
  _outDevices->writeTransportPage();
  _buitMachine->setState(_buitMachine->getTransportState());
}

void SceneEditState::longClick() {
  Serial.println("Going to Scene Settings!");
  _outDevices->printToScreen("State:", "Scene Settings!","");
  _buitMachine->setState(_buitMachine->getSceneSettingsState());
}

void SceneEditState::rotaryTurned(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void SceneEditState::threeAxisChanged(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void SceneEditState::trellisPressed(ControlCommand command) {
  Serial.printf("VALUE: %d\n", command.value);
  _sequencer->toggleSequence(command.value);
  _outDevices->writeSceneToNeoTrellis(_sequencer->getSequencesState());
}

void SceneEditState::trellisReleased(ControlCommand command) {
  Serial.println("Does nothing here!");
}