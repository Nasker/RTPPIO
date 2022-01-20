#pragma once

#include "VoidStateMachine.h"
#include "BuitOutDevicesManager.hpp"
#include "ControlCommand.h"
#include "constants.h"

class StateMachineManager{
    VoidStateMachine voidStateMachine;
 public:
    StateMachineManager();
    ~StateMachineManager();
    void connectOutDevices(const BuitOutDevicesManager& outDevices);
    void handleActions(ControlCommand callbackControlCommand);
};
