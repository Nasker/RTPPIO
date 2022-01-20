#include "Arduino.h"
#include "InitState.h"

  InitState::InitState(BuitStateMachine* voidMachine){
    Serial.println("InitState");
    _buitMachine = voidMachine;
  }

  void InitState::singleClick() {
    Serial.println("Going to Transport");
    _screen->print("State:", "Transport!");
    _buitMachine->setState(_buitMachine->getTransportState());
  }


  void InitState::doubleClick() {
    Serial.println("Going to Transport");
    _screen->print("State:", "Transport!");
    _buitMachine->setState(_buitMachine->getTransportState());
  }


  void InitState::tripleClick() {
    Serial.println("Going to Transport");
    _screen->print("State:", "Transport!");
    _buitMachine->setState(_buitMachine->getTransportState());
  }

  void InitState::longClick() {
    Serial.println("Going to Transport");
    _screen->print("State:", "Transport!");
    _buitMachine->setState(_buitMachine->getTransportState());
  }
