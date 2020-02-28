#include "Arduino.h"

#include "SequenceEditState.h"

  SequenceEditState::SequenceEditState(VoidStateMachine* voidMachine){
    Serial.println("SequenceEditState");
    _voidMachine = voidMachine;
  }

  void SequenceEditState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequenceEditState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _voidMachine->setState(_voidMachine->getSceneEditState());
  }


  void SequenceEditState::tripleClick() {
    Serial.println("Going to Sequence Piano Roll!");
    _voidMachine->setState(_voidMachine->getSequencePianoRollState());
  }

  void SequenceEditState::longClick() {
    Serial.println("Going to Sequence Settings!");
    _voidMachine->setState(_voidMachine->getSequenceSettingsState());
  }
