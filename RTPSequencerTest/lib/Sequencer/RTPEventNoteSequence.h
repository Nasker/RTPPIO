#include <LinkedList.h>
#include <RTPEventNote.h>
#include "Arduino.h"

class RTPEventNoteSequence{
  LinkedList<RTPEventNote*> EventNoteSequence = LinkedList<RTPEventNote*>();
  int _midiChannel;
  String _type;

public:
    RTPEventNoteSequence(int midiChannel, int NEvents, String type);
};
