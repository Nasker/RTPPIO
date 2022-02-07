#pragma once

#include <RTPEventNoteSequence.h>
#include "Structs.h"

class RTPScene{
  LinkedList <RTPEventNoteSequence*> SequencerScene = LinkedList<RTPEventNoteSequence*>();
  String _name;
  int _NSequences;
  int _selectedSequence;
  RTPSequenceNoteStates _seqStates;
public:
  RTPScene(String name, int NSequences);
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
  LinkedList<RTPEventNotePlus*>  getPlayedNotesList();
};
