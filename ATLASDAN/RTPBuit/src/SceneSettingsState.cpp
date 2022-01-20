#include "Arduino.h"

#include "SceneSettingsState.h"

  SceneSettingsState::SceneSettingsState (BuitStateMachine* buitMachine){
    Serial.println("SceneSettingsState");
    _buitMachine = buitMachine;
  }

  void SceneSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SceneSettingsState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _outDevices->printToScreen("State:", "Scene Edit!","");
    _buitMachine->setState(_buitMachine->getSceneEditState());
  }


  void SceneSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SceneSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
