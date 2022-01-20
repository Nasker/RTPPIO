#include "Arduino.h"

#include "SequenceSelectState.h"

  SequenceSelectState::SequenceSelectState(BuitStateMachine* voidMachine){
    Serial.println("SequenceSelectState");
    _buitMachine = voidMachine;
  }

  void SequenceSelectState::singleClick() {
    Serial.println("Going to Sequence Edit!");
    _screen->print("State:", "Sequence Edit!");
    _buitMachine->setState(_buitMachine->getSequenceEditState());
  }


  void SequenceSelectState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _screen->print("State:", "Scene Edit!");
    _buitMachine->setState(_buitMachine->getSceneEditState());
  }


  void SequenceSelectState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequenceSelectState::longClick() {
    Serial.println("Does nothing here!");
  }
