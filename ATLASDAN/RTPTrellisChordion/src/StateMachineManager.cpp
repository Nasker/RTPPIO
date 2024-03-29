/*
    Copyright 2021 Oscar Martínez
*/
#include "StateMachineManager.hpp"

StateMachineManager::StateMachineManager() {}

StateMachineManager::~StateMachineManager() {}

void StateMachineManager::connectDevices(const RTPScreen& screen) {
  voidStateMachine.setState(voidStateMachine.getInitState());
  voidStateMachine.connectScreen(screen);
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
