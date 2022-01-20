#include "Arduino.h"
#include "InitState.h"

  InitState::InitState(BuitStateMachine* buitMachine){
    Serial.println("InitState");
    _buitMachine = buitMachine;
  }

  void InitState::singleClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _buitMachine->setState(_buitMachine->getTransportState());
  }


  void InitState::doubleClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _buitMachine->setState(_buitMachine->getTransportState());
  }


  void InitState::tripleClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _buitMachine->setState(_buitMachine->getTransportState());
  }

  void InitState::longClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _buitMachine->setState(_buitMachine->getTransportState());
  }
