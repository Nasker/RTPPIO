#include "Arduino.h"

#include "SequenceEditState.h"

  SequenceEditState::SequenceEditState(BuitStateMachine* voidMachine){
    Serial.println("SequenceEditState");
    _buitMachine = voidMachine;
  }

  void SequenceEditState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequenceEditState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _screen->print("State:", "Scene Edit!");
    _buitMachine->setState(_buitMachine->getSceneEditState());
  }


  void SequenceEditState::tripleClick() {
    Serial.println("Going to Sequence Piano Roll!");
    _screen->print("State:", "Seq Piano Roll!");
    _buitMachine->setState(_buitMachine->getSequencePianoRollState());
  }

  void SequenceEditState::longClick() {
    Serial.println("Going to Sequence Settings!");
    _screen->print("State:", "Sequence Settings!");
    _buitMachine->setState(_buitMachine->getSequenceSettingsState());
  }
