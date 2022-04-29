#pragma once

#include "RTPOled.hpp"
#include "RTPNeoTrellis.hpp"
#include "RTPSequencer.h"
#include "Structs.h"
#include "RTPTypeColors.h"

class BuitDevicesManager {
    RTPOled _oled;
    RTPNeoTrellis* _neoTrellis;
    RTPSequencer* _sequencer;

public:
    BuitDevicesManager();
    void initSetup();
    void connectNeoTrellis(const RTPNeoTrellis& neoTrellis);
    void connectSequencer(const RTPSequencer& sequencer);
    void printToScreen(String firstLine, String secondLine, String thirdLine);
    void printToScreen(ControlCommand command);

    void selectScene(ControlCommand command);
    void selectSequence(ControlCommand command);

    void presentScene();
    void presentSequence();
    void presentTransport();

    void editScene(ControlCommand command);
    void editSequence(ControlCommand command);
    void useTransport(ControlCommand command);
private:
    void writeSequenceToNeoTrellis(RTPSequenceNoteStates sequenceStates, int color);
    void writeSceneToNeoTrellis(RTPSequencesState sequencesState);
    void writeTransportPage();
};