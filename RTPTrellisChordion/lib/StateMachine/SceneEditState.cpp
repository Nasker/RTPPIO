#include "Arduino.h"

#include "SceneEditState.h"

  SceneEditState::SceneEditState (VoidStateMachine* voidMachine){
    Serial.println("SceneEditState");
    _voidMachine = voidMachine;
  }

  void SceneEditState::singleClick() {
    Serial.println("Going to Sequence Select!");
    _voidMachine->setState(_voidMachine->getSequenceSelectState());
  }


  void SceneEditState::doubleClick() {
    Serial.println("Going to Transport");
    _voidMachine->setState(_voidMachine->getTransportState());
  }


  void SceneEditState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SceneEditState::longClick() {
    Serial.println("Going to Scene Settings!");
    _voidMachine->setState(_voidMachine->getSceneSettingsState());
  }
