#pragma once

#include <LinkedList.h>
#include <RTPScene.h>
#include "NotesPlayer.hpp"
#include "Structs.h"
#include <vector>
#include "MusicManager.hpp"
using namespace std;

class RTPSequencer{
  vector<RTPScene> Sequencer;
  int _NScenes;
  int _selectedScene;
  NotesPlayer _notesPlayer;

public:
  RTPSequencer(int NScenes);
  void connectMusicManager(const MusicManager& musicManager);
  void playAndMoveSequencer();
  void stopAndCleanSequencer();
  void pauseSequencer();
  void selectScene(int scene);
  void increaseSelectedScene();
  void decreaseSelectedScene();
  int getSelectScene();
  void addScene(RTPScene scene);
  void removeScene(int scene);
  void toggleSequence(int sequenceIndex);
  RTPSequencesState getSequencesState();
  void selectSequence(int sequenceIndex);
  RTPSequenceNoteStates getSelectedSequenceNoteStates();
  void toggleNoteInSceneInSelectedSequence(int position);
  void editNoteInCurrentPosition(ControlCommand command);
  int getSelectedSequenceColor();
  void dumpSequencesToJson();
};
