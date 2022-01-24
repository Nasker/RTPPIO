#pragma once

#include "BuitStateMachine.h"
#include "RTPSequencer.h"
#include "BuitOutDevicesManager.hpp"
#include "ControlCommand.h"
#include "constants.h"

class StateMachineManager{
    BuitStateMachine buitStateMachine;
 public:
    StateMachineManager();
    ~StateMachineManager();
    void connectOutDevices(const BuitOutDevicesManager& outDevices);
    void connectSequencer(const RTPSequencer& sequencer);
    void handleActions(ControlCommand callbackControlCommand);
};
