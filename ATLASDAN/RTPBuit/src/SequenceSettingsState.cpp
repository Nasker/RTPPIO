#include "Arduino.h"

#include "SequenceSettingsState.h"

  SequenceSettingsState::SequenceSettingsState(BuitStateMachine* buitMachine){
    Serial.println("SequenceSettingsState");
    _buitMachine = buitMachine;
  }

  void SequenceSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequenceSettingsState::doubleClick() {
    Serial.println("Going to Sequence Edit!");
    _outDevices->printToScreen("State:", "Sequence Edit!","");
    _buitMachine->setState(_buitMachine->getSequenceEditState());
  }


  void SequenceSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequenceSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
