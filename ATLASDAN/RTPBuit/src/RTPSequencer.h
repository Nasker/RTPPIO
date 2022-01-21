#pragma once

#include <LinkedList.h>
#include <RTPScene.h>
#include "Structs.h"

class RTPSequencer{
  LinkedList<RTPScene*> Sequencer = LinkedList<RTPScene*>();
  int _NScenes;
  int _selectedScene;
public:
  RTPSequencer(int NScenes);
  void playAndMoveSequencer();
  void stopAndCleanSequencer();
  void pauseSequencer();
  void selectScene(int scene);
  int getSelectScene();
  void addScene(RTPScene* scene);
  void removeScene(int scene);
  void toggleNoteInScene(int position);
  void toggleSequence(int sequenceIndex);
  RTPSequencesState getSequencesState();
};
