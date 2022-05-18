#pragma once

#include "Adafruit_NeoTrellis.h"
#include "Structs.h"
#include "ControlCommand.h"
#include "constants.h"

class RTPMainUnit;
class RTPNeoTrellis{
    static Adafruit_NeoTrellis myTrellis;
    static RTPMainUnit* mainUnit;
 public:
    RTPNeoTrellis();
    void begin(RTPMainUnit* _mainUnit);
    static TrellisCallback blink(keyEvent evt);
    void read();
    void writeSequenceStates(RTPSequenceNoteStates seqStates, int color);
    void writeSceneStates(RTPSequencesState sceneStates);
    void writeTransportPage(int color);
    void writeBuitCCStates(RTPSequenceNoteStates buitCCStates);
    //void callbackFromTrellis(void(*userFunc)(String,int));
    //void callbackFromNeoTrellis(RTPMainUnit*);
};