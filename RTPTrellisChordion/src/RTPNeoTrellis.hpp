#pragma once

#include "Adafruit_NeoTrellis.h"
#include "ControlCommand.h"
#include "constants.h"

class RTPMainUnit;
Adafruit_NeoTrellis myTrellis;
class RTPNeoTrellis{
    
 public:
    RTPNeoTrellis();
    void begin();
    //TrellisCallback blink(keyEvent evt);
    void callbackFromTrellis(void(*userFunc)(String,int));
    void callbackFromNeoTrellis(RTPMainUnit*);
};