/*
    Copyright 2021 Oscar Martínez
*/
#include "StateMachineManager.hpp"

StateMachineManager::StateMachineManager() {}

StateMachineManager::~StateMachineManager() {}

void StateMachineManager::connectOutDevices(const BuitOutDevicesManager& outDevices) {
  voidStateMachine.setState(voidStateMachine.getInitState());
  voidStateMachine.connectOutDevices(outDevices);
}

void StateMachineManager::handleActions(ControlCommand callbackControlCommand) {
  switch(callbackControlCommand.commandType){
          case SINGLE_CLICK:
            voidStateMachine.singleClick();
            break;
          case DOUBLE_CLICK:
            voidStateMachine.doubleClick();
            break;
          case TRIPLE_CLICK:
            voidStateMachine.tripleClick();
            break;
          case LONG_CLICK:
            voidStateMachine.longClick();
            break;
        }
}
