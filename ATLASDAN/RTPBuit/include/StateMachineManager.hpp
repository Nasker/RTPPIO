#pragma once

#include "BuitStateMachine.h"
#include "BuitDevicesManager.hpp"
#include "ControlCommand.h"
#include "constants.h"

class StateMachineManager{
    BuitStateMachine buitStateMachine;
 public:
    StateMachineManager();
    ~StateMachineManager();
    void connectDevices(const BuitDevicesManager& outDevices);
    void handleActions(ControlCommand callbackControlCommand);
};
