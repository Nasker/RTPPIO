#pragma once

#include "Arduino.h"
#include "VoidStateMachine.h"
#include <RTPRotaryClick.h>

#define ROT_RIGHT_PIN 2
#define ROT_LEFT_PIN 3
#define BUTTON_PIN 4

RTPRotaryClick rotaryClick(ROT_RIGHT_PIN, ROT_LEFT_PIN, BUTTON_PIN, LOW, true);
VoidState* initState;
VoidStateMachine voidStateMachine(initState);

//extern RTPScreen* rtpScreen;

class RTPMainUnit{
  //RTPTrellis* rtpTrellis;
public:
  RTPMainUnit();
  void begin();
  void update();
  void actOnTrellisCallback(String callbackString, int buttonNumber);
};
