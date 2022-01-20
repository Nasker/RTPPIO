#include "Arduino.h"
#include "TransportState.h"

  TransportState::TransportState (BuitStateMachine* voidMachine){
    Serial.println("TransportState");
    _buitMachine = voidMachine;
  }

  void TransportState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void TransportState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _screen->print("State:", "Scene Edit!");
    _buitMachine->setState(_buitMachine->getSceneEditState());
  }


  void TransportState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void TransportState::longClick() {
    Serial.println("Going to Global Settings!");
    _screen->print("State:", "Global Settings!");
    _buitMachine->setState(_buitMachine->getGlobalSettingsState());
  }
