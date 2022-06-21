#pragma once

#include "RTPOled.hpp"
#include "RTPNeoTrellis.hpp"
#include "RTPSequencer.h"
#include "MatrixBuitControlChanger.hpp"
#include "Structs.h"
#include "RTPTypeColors.h"
#include "RTPSDManager.hpp"

class BuitDevicesManager {
    RTPOled _oled;
    RTPNeoTrellis* _neoTrellis;
    RTPSequencer* _sequencer;
    MatrixBuitControlChanger _matrixBuitCC;

public:
    BuitDevicesManager();
    void initSetup();
    void connectNeoTrellis(const RTPNeoTrellis& neoTrellis);
    void connectSequencer(const RTPSequencer& sequencer);
    void connectMusicManager(const MusicManager& musicManager);
    void printToScreen(String firstLine, String secondLine, String thirdLine);
    void printToScreen(ControlCommand command);

    void selectScene(ControlCommand command);
    void selectSequence(ControlCommand command);

    void presentScene();
    void presentSequence();
    void presentTransport();
    void presentBuitCC();

    void editScene(ControlCommand command);
    void editSequence(ControlCommand command);
    void useTransport(ControlCommand command);
    void editCurrentNote(ControlCommand command);

    void changeScene(ControlCommand command);
    void nudgePage(ControlCommand command);

    void editBuitCC(ControlCommand command);
    void sendBuitCC(ControlCommand command);

    void dumpSequencesToJson();
private:
    void writeSequenceToNeoTrellis(RTPSequenceNoteStates sequenceStates, int color);
    void writeSceneToNeoTrellis(RTPSequencesState sequencesState);
    void writeTransportPage();
};