#pragma once

#include "Arduino.h"
#include "MIDI.h"
#include "RTPScreen.hpp"
#include "RTPTrellis.hpp"
//#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickChordion.hpp"
#include "ThreeAxisRange.hpp"
#include "ChordionKeys.hpp"
#include "Adafruit_NeoTrellis.h"

//extern RTPScreen* rtpScreen;
  
class RTPMainUnit{
  RTPTrellis* rtpTrellis;
  //RTPNeoTrellis* rtpNeotrellis;
  RTPRotaryClickChordion* rtpRotary;
  RTPScreen* rtpScreen;
  ThreeAxisRange* threeAxisRange;
  ChordionKeys chordionKeys;
  int baseNote = BASE_NOTE;
public:
  RTPMainUnit();
  void begin();
  void update();
  void updatePeriodically();
  void actOnThreeAxisCallback(String callbackString, int rangeValue);
  void actOnControlsCallback(ControlCommand answer);
  /*void actOnThreeAxisCallback(ControlCommand answer);
  void actOnTrellisCallback(String callbackString, int buttonNumber);
  void actOnRotationCallback(String callbackString, int position);
  void actOnClickCallback(String callbackString);*/
};
