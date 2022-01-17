#pragma once

#include <Arduino.h>
#include "ThreeAxisPing.h"
#include "ControlCommand.h"

class RTPMainUnit;
class ThreeAxisRange{
    ThreeAxisPing* threeAxisPing;
    int pLeftRange, pCenterRange, pRightRange;
    public:
    ThreeAxisRange();
    void callbackFromThreeAxis(RTPMainUnit*);

};