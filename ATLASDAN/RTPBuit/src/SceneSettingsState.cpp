#include "Arduino.h"

#include "SceneSettingsState.h"

  SceneSettingsState::SceneSettingsState (VoidStateMachine* voidMachine){
    Serial.println("SceneSettingsState");
    _voidMachine = voidMachine;
  }

  void SceneSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SceneSettingsState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _outDevices->printToScreen("State:", "Scene Edit!","");
    _voidMachine->setState(_voidMachine->getSceneEditState());
  }


  void SceneSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SceneSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
