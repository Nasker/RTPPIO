#pragma once

#include "VoidStateMachine.h"
#include "RTPScreen.hpp"
#include "ControlCommand.h"
#include "constants.h"

class StateMachineManager{
    VoidStateMachine voidStateMachine;
 public:
    StateMachineManager();
    ~StateMachineManager();
    void connectDevices(const RTPScreen& screen);
    void handleActions(ControlCommand callbackControlCommand);
};
