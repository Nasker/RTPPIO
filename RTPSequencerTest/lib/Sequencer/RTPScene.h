#include <RTPEventNoteSequence.h>
#include "Arduino.h"

class RTPScene{
  LinkedList <RTPEventNoteSequence*> SequencerScene = LinkedList<RTPEventNoteSequence*>();
  String _name;
  int _NSequences;

public:
  RTPScene(String name, int NSequences);
};
