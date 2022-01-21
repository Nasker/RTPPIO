#pragma once

#include "RTPOled.hpp"
#include "RTPNeoTrellis.hpp"
#include "Structs.h"

class BuitOutDevicesManager {
    RTPOled _oled;
    RTPNeoTrellis* _neoTrellis;
public:
    BuitOutDevicesManager();
    void initSetup();
    void connectNeoTrellis(const RTPNeoTrellis& neoTrellis);
    void printToScreen(String firstLine, String secondLine, String thirdLine);
    void printToScreen(ControlCommand command);
    void writeSequenceToNeoTrellis(RTPSequenceNoteStates sequenceStates, int color);
    void writeSceneToNeoTrellis(RTPSequencesState sequencesState);
};