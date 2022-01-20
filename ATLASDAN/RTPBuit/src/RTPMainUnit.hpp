#pragma once

#include "Arduino.h"
#include <Wire.h>
#include "MIDI.h"
#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickChordion.hpp"
#include "RTPOled.hpp"
#include "RTPThreeAxisVL.hpp"
#include "ChordionKeys.hpp"
  
class RTPMainUnit{
  RTPNeoTrellis rtpTrellis;
  RTPRotaryClickDev rtpRotary{ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true};
  RTPThreeAxisVL vlSensor;
  RTPOled display;
  ChordionKeys chordionKeys;
  int baseNote = BASE_NOTE;
public:
  RTPMainUnit();
  void begin();
  void update();
  void updatePeriodically();
  void actOnThreeAxisCallback(String callbackString, int rangeValue);
  void actOnControlsCallback(ControlCommand answer);
};
