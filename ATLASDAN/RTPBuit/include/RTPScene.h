#pragma once

#include "RTPEventNoteSequence.h"
#include "Structs.h"
#include "LinkedList.h"
#include <vector>
using namespace std;

class RTPScene{
  vector<RTPEventNoteSequence> SequencerScene;
  String _name;
  int _NSequences;
  int _selectedSequence;
  RTPSequenceNoteStates _seqStates;
public:
  RTPScene(String name, int NSequences);
  void connectNotesPlayer(const NotesPlayer& notesPlayer);
  void playScene();
  void fordwardScene();
  void backwardScene();
  void resetScene();
  void setSelectedSequence(int selectedSequence);
  int getSelectedSequence();
  int getSize();
  RTPSequenceNoteStates getSelectedSequenceNoteStates();
  RTPSequencesState getSequencesState();
  void selectParameterInSequece(int parameterIndex);
  void incselectParameterInSequece();
  void decselectParameterInSequece();
  int getSelectedParameterInSequeceValue();
  int getSequenceType(int sequenceIndex);
  void toggleSequence(int sequenceIndex);
  void toggleNoteInSequence(int position);
  RTPSequenceNoteStates getSequenceNoteStates();
  int getSequenceColor();
  //LinkedList<RTPEventNotePlus*>  getPlayedNotesList();
};
