#include "Arduino.h"
#include "InitState.h"

  InitState::InitState(VoidStateMachine* voidMachine){
    Serial.println("InitState");
    _voidMachine = voidMachine;
  }

  void InitState::singleClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _voidMachine->setState(_voidMachine->getTransportState());
  }


  void InitState::doubleClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _voidMachine->setState(_voidMachine->getTransportState());
  }


  void InitState::tripleClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _voidMachine->setState(_voidMachine->getTransportState());
  }

  void InitState::longClick() {
    Serial.println("Going to Transport");
    _outDevices->printToScreen("State:", "Transport!","");
    _voidMachine->setState(_voidMachine->getTransportState());
  }
