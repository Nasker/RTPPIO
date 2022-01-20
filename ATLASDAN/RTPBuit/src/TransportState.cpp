#include "Arduino.h"
#include "TransportState.h"

  TransportState::TransportState (VoidStateMachine* voidMachine){
    Serial.println("TransportState");
    _voidMachine = voidMachine;
  }

  void TransportState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void TransportState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _outDevices->printToScreen("State:", "Scene Edit!","");
    _voidMachine->setState(_voidMachine->getSceneEditState());
  }


  void TransportState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void TransportState::longClick() {
    Serial.println("Going to Global Settings!");
    _outDevices->printToScreen("State:", "Global Settings!","");
    _voidMachine->setState(_voidMachine->getGlobalSettingsState());
  }
