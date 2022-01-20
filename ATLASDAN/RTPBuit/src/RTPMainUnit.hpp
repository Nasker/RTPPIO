#pragma once

#include "Arduino.h"
#include <Wire.h>
#include "MIDI.h"
#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickChordion.hpp"
#include "RTPThreeAxisVL.hpp"
#include "ChordionKeys.hpp"
#include "BuitOutDevicesManager.hpp"
#include "StateMachineManager.hpp"
  
class RTPMainUnit{
  RTPNeoTrellis rtpTrellis;
  RTPRotaryClickDev rtpRotary{ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true};
  RTPThreeAxisVL vlSensor;
  BuitOutDevicesManager outDevicesManager;
  StateMachineManager stateMachineManager;
  ChordionKeys chordionKeys;
  int baseNote = BASE_NOTE;
public:
  RTPMainUnit();
  void begin();
  void update();
  void actOnThreeAxisCallback(String callbackString, int rangeValue);
  void actOnControlsCallback(ControlCommand answer);
};
