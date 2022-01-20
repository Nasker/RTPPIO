#include "Arduino.h"

#include "SequencePianoRollState.h"

  SequencePianoRollState::SequencePianoRollState(BuitStateMachine* buitMachine){
    Serial.println("SequencePianoRollState");
    _buitMachine = buitMachine;
  }

  void SequencePianoRollState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequencePianoRollState::doubleClick() {
    Serial.println("Going to Sequence Edit!");
    _outDevices->printToScreen("State:", "Sequence Edit!","");
    _buitMachine->setState(_buitMachine->getSequenceEditState());
  }


  void SequencePianoRollState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequencePianoRollState::longClick() {
    Serial.println("Does nothing here!");
  }
