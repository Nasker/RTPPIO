#include "Arduino.h"

#include "SequenceSettingsState.h"

  SequenceSettingsState::SequenceSettingsState(BuitStateMachine* voidMachine){
    Serial.println("SequenceSettingsState");
    _buitMachine = voidMachine;
  }

  void SequenceSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequenceSettingsState::doubleClick() {
    Serial.println("Going to Sequence Edit!");
    _screen->print("State:", "Sequence Edit!");
    _buitMachine->setState(_buitMachine->getSequenceEditState());
  }


  void SequenceSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequenceSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
