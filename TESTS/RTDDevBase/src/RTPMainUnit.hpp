#pragma once

#include "Arduino.h"
#include <Wire.h>
#include "MIDI.h"
#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickDev.hpp"
#include "RTPOled.hpp"
#include "RTPThreeAxisVL.hpp"
  
class RTPMainUnit{
  RTPNeoTrellis rtpTrellis;
  RTPRotaryClickDev rtpRotary{ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true};
  RTPThreeAxisVL vlSensor;
  RTPOled display;
public:
  RTPMainUnit();
  void begin();
  void update();
  void updatePeriodically();
  void actOnThreeAxisCallback(String callbackString, int rangeValue);
  void actOnControlsCallback(ControlCommand answer);
};
