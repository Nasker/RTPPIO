#include "Arduino.h"

#include "GlobalSettingsState.h"

  GlobalSettingsState::GlobalSettingsState (BuitStateMachine* buitMachine){
    Serial.println("GlobalSettingsState");
    _buitMachine = buitMachine;
  }

  void GlobalSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void GlobalSettingsState::doubleClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("Transport", "", "");
    _buitMachine->setState(_buitMachine->getTransportState());
  }


  void GlobalSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void GlobalSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
