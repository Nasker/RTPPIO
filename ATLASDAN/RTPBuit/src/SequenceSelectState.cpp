#include "Arduino.h"

#include "SequenceSelectState.h"

  SequenceSelectState::SequenceSelectState(VoidStateMachine* voidMachine){
    Serial.println("SequenceSelectState");
    _voidMachine = voidMachine;
  }

  void SequenceSelectState::singleClick() {
    Serial.println("Going to Sequence Edit!");
    _outDevices->printToScreen("State:", "Sequence Edit!","");
    _voidMachine->setState(_voidMachine->getSequenceEditState());
  }


  void SequenceSelectState::doubleClick() {
    Serial.println("Going to Scene Edit!");
    _outDevices->printToScreen("State:", "Scene Edit!","");
    _voidMachine->setState(_voidMachine->getSceneEditState());
  }


  void SequenceSelectState::tripleClick() {
    Serial.println("Does nothing here!");
  }

  void SequenceSelectState::longClick() {
    Serial.println("Does nothing here!");
  }
