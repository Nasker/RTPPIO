#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_Trellis.h"
#include "ControlCommand.h"

#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)

class RTPMainUnit;
class RTPTrellis{
  Adafruit_Trellis matrix0 = Adafruit_Trellis();
  Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
public:
  RTPTrellis();
  void begin();
  //void callbackFromTrellis(void(*userFunc)(String,int));
  void callbackFromTrellis(RTPMainUnit*);
};
