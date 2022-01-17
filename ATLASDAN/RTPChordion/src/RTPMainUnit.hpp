#pragma once
#define NEO_TRELLIS

#include "Arduino.h"
#include <Wire.h>
#include "MIDI.h"
#include "RTPTrellis.hpp"
#include "RTPNeoTrellis.hpp"
#include "RTPRotaryClickChordion.hpp"
#include "ChordionKeys.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_NeoTrellis.h"
#include "RTPThreeAxisVL.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
  
class RTPMainUnit{
  #ifdef NEO_TRELLIS
    RTPNeoTrellis rtpTrellis;
  #else
    RTPTrellis rtpTrellis;
  #endif
  
  RTPRotaryClickChordion rtpRotary{ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true};
  RTPThreeAxisVL vlSensor;
  Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS};
  ChordionKeys chordionKeys;
  int baseNote = BASE_NOTE;

public:
  RTPMainUnit();
  void begin();
  void update();
  void updatePeriodically();
  void actOnThreeAxisCallback(String callbackString, int rangeValue);
  void actOnControlsCallback(ControlCommand answer);
  void printToScreen(ControlCommand command);
  /*void actOnThreeAxisCallback(ControlCommand answer);
  void actOnTrellisCallback(String callbackString, int buttonNumber);
  void actOnRotationCallback(String callbackString, int position);
  void actOnClickCallback(String callbackString);*/
};
