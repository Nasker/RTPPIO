#pragma once

#include <LinkedList.h>
#include <RTPScene.h>
#include "NotesPlayer.hpp"
#include "Structs.h"
#include <vector>
using namespace std;

class RTPSequencer{
  vector<RTPScene> Sequencer;
  int _NScenes;
  int _selectedScene;
  NotesPlayer _notesPlayer;

public:
  RTPSequencer(int NScenes);
  void playAndMoveSequencer();
  void stopAndCleanSequencer();
  void pauseSequencer();
  void selectScene(int scene);
  int getSelectScene();
  void addScene(RTPScene scene);
  void removeScene(int scene);
  void toggleSequence(int sequenceIndex);
  RTPSequencesState getSequencesState();
  void selectSequence(int sequenceIndex);
  RTPSequenceNoteStates getSelectedSequenceNoteStates();
  void toggleNoteInSceneInSelectedSequence(int position);
  int getSelectedSequenceColor();
};
