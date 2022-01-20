#pragma once

#include "BuitStateMachine.h"
#include "BuitOutDevicesManager.hpp"
#include "ControlCommand.h"
#include "constants.h"

class StateMachineManager{
    BuitStateMachine buitStateMachine;
 public:
    StateMachineManager();
    ~StateMachineManager();
    void connectOutDevices(const BuitOutDevicesManager& outDevices);
    void handleActions(ControlCommand callbackControlCommand);
};
