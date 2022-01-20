#include "Arduino.h"

#include "SequenceEditState.h"

  SequenceEditState::SequenceEditState(BuitStateMachine* buitMachine){
    Serial.println("SequenceEditState");
    _buitMachine = buitMachine;
  }

  void SequenceEditState::singleClick() {
    Serial.println("Does nothing here!");
  }


  void SequenceEditState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _outDevices->printToScreen("State:", "Scene Edit!","");
    _buitMachine->setState(_buitMachine->getSceneEditState());
  }


  void SequenceEditState::tripleClick() {
    Serial.println("Going to Sequence Piano Roll!");
    _outDevices->printToScreen("State:", "Seq Piano Roll!","");
    _buitMachine->setState(_buitMachine->getSequencePianoRollState());
  }

  void SequenceEditState::longClick() {
    Serial.println("Going to Sequence Settings!");
    _outDevices->printToScreen("State:", "Sequence Settings!","");
    _buitMachine->setState(_buitMachine->getSequenceSettingsState());
  }
