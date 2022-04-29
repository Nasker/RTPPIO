#include "Arduino.h"

#include "SceneEditState.h"

SceneEditState::SceneEditState (BuitStateMachine* buitMachine){
  Serial.println("SceneEditState");
  _buitMachine = buitMachine;
}

void SceneEditState::singleClick() {
  Serial.println("Going to Sequence Select!");
  _devices->printToScreen("Sequence Select", "", "");
  _buitMachine->setState(_buitMachine->getSequenceSelectState());
}

void SceneEditState::doubleClick() {
  Serial.println("Going to Transport");
  _devices->presentTransport();
  _buitMachine->setState(_buitMachine->getTransportState());
}

void SceneEditState::longClick() {
  Serial.println("Going to Scene Settings!");
  _devices->printToScreen("Scene Settings", "","");
  _buitMachine->setState(_buitMachine->getSceneSettingsState());
}

void SceneEditState::rotaryTurned(ControlCommand command) {
}

void SceneEditState::threeAxisChanged(ControlCommand command) {
}

void SceneEditState::trellisPressed(ControlCommand command) { 
  _devices->editScene(command);
}

void SceneEditState::trellisReleased(ControlCommand command) {
}