#pragma once

#include <RTPEventNoteSequence.h>

class RTPScene{
  LinkedList <RTPEventNoteSequence*> SequencerScene = LinkedList<RTPEventNoteSequence*>();
  String _name;
  int _NSequences;
  int _selectedSequence;

public:
  RTPScene(String name, int NSequences);
  void fordwardScene();
  void backwardScene();
  void resetScene();
  void setSelectedSequence(int selectedSequence);
  int getSelectedSequence();
  void selectParameterInSequece(int parameterIndex);
  void incselectParameterInSequece();
  void decselectParameterInSequece();
  int getSelectedParameterInSequeceValue();
  int getSequenceType(int sequenceIndex);
  void toggleNoteInSequence(int position);
  LinkedList<RTPEventNotePlus*>  getPlayedNotesList();
};
