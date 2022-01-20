#include "Arduino.h"

#include "SequencePianoRollState.h"

  SequencePianoRollState::SequencePianoRollState(BuitStateMachine* voidMachine){
    Serial.println("SequencePianoRollState");
    _buitMachine = voidMachine;
  }

  void SequencePianoRollState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequencePianoRollState::doubleClick() {
    Serial.println("Going to Sequence Edit!");
    _screen->print("State:", "Sequence Edit!");
    _buitMachine->setState(_buitMachine->getSequenceEditState());
  }


  void SequencePianoRollState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequencePianoRollState::longClick() {
    Serial.println("Does nothing here!");
  }
