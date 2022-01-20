/*
    Copyright 2021 Oscar Martínez
*/
#include "StateMachineManager.hpp"

StateMachineManager::StateMachineManager() {}

StateMachineManager::~StateMachineManager() {}

void StateMachineManager::connectOutDevices(const BuitOutDevicesManager& outDevices) {
  buitStateMachine.setState(buitStateMachine.getInitState());
  buitStateMachine.connectOutDevices(outDevices);
}

void StateMachineManager::handleActions(ControlCommand callbackControlCommand) {
  switch(callbackControlCommand.commandType){
          case SINGLE_CLICK:
            buitStateMachine.singleClick();
            break;
          case DOUBLE_CLICK:
            buitStateMachine.doubleClick();
            break;
          case TRIPLE_CLICK:
            buitStateMachine.tripleClick();
            break;
          case LONG_CLICK:
            buitStateMachine.longClick();
            break;
        }
}
