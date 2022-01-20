#include "Arduino.h"

#include "GlobalSettingsState.h"

  GlobalSettingsState::GlobalSettingsState (BuitStateMachine* voidMachine){
    Serial.println("GlobalSettingsState");
    _buitMachine = voidMachine;
  }

  void GlobalSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void GlobalSettingsState::doubleClick() {
    Serial.println("Going to Transport");
    _screen->print("State:", "Transport!");
    _buitMachine->setState(_buitMachine->getTransportState());
  }


  void GlobalSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void GlobalSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
