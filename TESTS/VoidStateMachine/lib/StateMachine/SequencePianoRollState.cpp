#include "Arduino.h"

#include "SequencePianoRollState.h"

  SequencePianoRollState::SequencePianoRollState(VoidStateMachine* voidMachine){
    Serial.println("SequencePianoRollState");
    _voidMachine = voidMachine;
  }

  void SequencePianoRollState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequencePianoRollState::doubleClick() {
    Serial.println("Going to Sequence Edit!");
    _voidMachine->setState(_voidMachine->getSequenceEditState());
  }


  void SequencePianoRollState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequencePianoRollState::longClick() {
    Serial.println("Does nothing here!");
  }
