#pragma once

#include <LinkedList.h>
#include <RTPScene.h>

class RTPSequencer{
  LinkedList<RTPScene*> Sequencer = LinkedList<RTPScene*>();
  int _NScenes;
public:
    RTPSequencer(int NScenes);
    void playAndMoveSequencer();
    void stopAndCleanSequencer();
    void pauseSequencer();
};
