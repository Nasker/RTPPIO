#pragma once

#include "Arduino.h"
#include <Wire.h>
#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickChordion.hpp"
#include "RTPThreeAxisVL.hpp"
#include "BuitOutDevicesManager.hpp"
#include "StateMachineManager.hpp"
#include "RTPSequencer.h"
#include "RTPSequencerManager.hpp"
  
class RTPMainUnit{
  RTPNeoTrellis rtpTrellis;
  RTPRotaryClickDev rtpRotary{ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true};
  RTPThreeAxisVL vlSensor;
  BuitOutDevicesManager outDevicesManager;
  StateMachineManager stateMachineManager;
  RTPSequencer Sequencer{1};
  RTPSequencerManager SequencerManager;
public:
  RTPMainUnit();
  void begin();
  void update();
  void linkToSequencerManager(byte realtimebyte);
  void actOnThreeAxisCallback(String callbackString, int rangeValue);
  void actOnControlsCallback(ControlCommand answer);
};
