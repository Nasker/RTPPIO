#include "Arduino.h"

#include "SequenceSettingsState.h"

  SequenceSettingsState::SequenceSettingsState(VoidStateMachine* voidMachine){
    Serial.println("SequenceSettingsState");
    _voidMachine = voidMachine;
  }

  void SequenceSettingsState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequenceSettingsState::doubleClick() {
    Serial.println("Going to Sequence Edit!");
    _voidMachine->setState(_voidMachine->getSequenceEditState());
  }


  void SequenceSettingsState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequenceSettingsState::longClick() {
    Serial.println("Does nothing here!");
  }
