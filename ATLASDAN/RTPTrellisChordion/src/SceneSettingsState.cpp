#include "Arduino.h"

#include "SceneSettingsState.h"

  SceneSettingsState::SceneSettingsState (BuitStateMachine* voidMachine){
    Serial.println("SceneSettingsState");
    _buitMachine = voidMachine;
  }

  void SceneSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SceneSettingsState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _screen->print("State:", "Scene Edit!");
    _buitMachine->setState(_buitMachine->getSceneEditState());
  }


  void SceneSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SceneSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
