#include "Arduino.h"

#include "SceneEditState.h"

  SceneEditState::SceneEditState (BuitStateMachine* voidMachine){
    Serial.println("SceneEditState");
    _buitMachine = voidMachine;
  }

  void SceneEditState::singleClick() {
    Serial.println("Going to Sequence Select!");
    _screen->print("State:", "Sequence Select!");
    _buitMachine->setState(_buitMachine->getSequenceSelectState());
  }


  void SceneEditState::doubleClick() {
    Serial.println("Going to Transport");
    _screen->print("State:", "Transport!");
    _buitMachine->setState(_buitMachine->getTransportState());
  }


  void SceneEditState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SceneEditState::longClick() {
    Serial.println("Going to Scene Settings!");
    _screen->print("State:", "Scene Settings!");
    _buitMachine->setState(_buitMachine->getSceneSettingsState());
  }
