#include "Arduino.h"

#include "GlobalSettingsState.h"

  GlobalSettingsState::GlobalSettingsState (VoidStateMachine* voidMachine){
    Serial.println("GlobalSettingsState");
    _voidMachine = voidMachine;
  }

  void GlobalSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void GlobalSettingsState::doubleClick() {
    Serial.println("Going to Transport");
    _screen->print("State:", "Transport!");
    _voidMachine->setState(_voidMachine->getTransportState());
  }


  void GlobalSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void GlobalSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
