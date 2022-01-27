#pragma once

#include "Arduino.h"
#include <Wire.h>
#include "MIDI.h"
#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickChordion.hpp"
#include "RTPThreeAxisVL.hpp"
#include "ChordionKeys.hpp"
#include "BuitDevicesManager.hpp"
#include "StateMachineManager.hpp"
#include "RTPSequencer.h"
#include "RTPSequencerManager.hpp"
  
class RTPMainUnit{
  RTPNeoTrellis rtpTrellis;
  RTPRotaryClickDev rtpRotary{ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true};
  RTPThreeAxisVL vlSensor;
  BuitDevicesManager devicesManager;
  StateMachineManager stateMachineManager;
  RTPSequencer Sequencer{1};
  RTPSequencerManager SequencerManager;
  ChordionKeys chordionKeys;
  int baseNote = BASE_NOTE;
public:
  RTPMainUnit();
  void begin();
  void update();
  void linkToSequencerManager(byte realtimebyte);
  void actOnThreeAxisCallback(String callbackString, int rangeValue);
  void actOnControlsCallback(ControlCommand answer);
};
