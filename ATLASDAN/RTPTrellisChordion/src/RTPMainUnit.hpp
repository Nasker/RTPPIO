#pragma once
//#define NEO_TRELLIS

#include "Arduino.h"
#include "MIDI.h"
#include "RTPScreen.hpp"
#include "RTPTrellis.hpp"
#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickChordion.hpp"
#include "ChordionKeys.hpp"
#include "Adafruit_NeoTrellis.h"
#include "StateMachineManager.hpp"
  
class RTPMainUnit{
  #ifdef NEO_TRELLIS
    RTPNeoTrellis rtpTrellis;
  #else
    RTPTrellis rtpTrellis;
  #endif
  
  RTPRotaryClickChordion rtpRotary{ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true};
  RTPScreen rtpScreen;
  ChordionKeys chordionKeys;
  int baseNote = BASE_NOTE;
  StateMachineManager machineManager;

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
