#pragma once

#include <RTPEventNoteSequence.h>

class RTPScene{
  LinkedList <RTPEventNoteSequence*> SequencerScene = LinkedList<RTPEventNoteSequence*>();
  String _name;
  int _NSequences;

public:
  RTPScene(String name, int NSequences);
  void fordwardScene();
  void backwardScene();
  void resetScene();
  int getSequenceType(int sequenceIndex);
  LinkedList<RTPEventNotePlus*>  getPlayedNotesList();
  void editSceneSequenceBlock(int sequence, LinkedList<RTPEventNote*> displayedEventsList, int NsequenceBlock);
};
