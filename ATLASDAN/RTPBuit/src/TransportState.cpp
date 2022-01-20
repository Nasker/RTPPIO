#include "Arduino.h"
#include "TransportState.h"

  TransportState::TransportState (BuitStateMachine* buitMachine){
    Serial.println("TransportState");
    _buitMachine = buitMachine;
  }

  void TransportState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void TransportState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _outDevices->printToScreen("State:", "Scene Edit!","");
    _buitMachine->setState(_buitMachine->getSceneEditState());
  }


  void TransportState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void TransportState::longClick() {
    Serial.println("Going to Global Settings!");
    _outDevices->printToScreen("State:", "Global Settings!","");
    _buitMachine->setState(_buitMachine->getGlobalSettingsState());
  }
