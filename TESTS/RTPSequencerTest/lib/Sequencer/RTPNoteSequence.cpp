#include "RTPEventNoteSequence.h"

RTPEventNoteSequence::RTPEventNoteSequence(int midiChannel, int NEvents, String type){
  _midiChannel = midiChannel;
  _type = type;
  for(int i=0; i < NEvents; i++){
    RTPEventNote *eventNote = new RTPEventNote(false, 0);
    EventNoteSequence.add(eventNote);
  }
}
