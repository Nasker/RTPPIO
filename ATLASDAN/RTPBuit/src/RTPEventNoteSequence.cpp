#include <RTPEventNoteSequence.h>
#include "RTPEventNotePlus.h"
#define SEQ_BLOCK_SIZE 16

RTPEventNoteSequence::RTPEventNoteSequence(int midiChannel, int NEvents, int type){
  _midiChannel = midiChannel;
  _type = type;
  _currentPosition = 0;
  _isRecording = false;
  _isEnabled = true;
  for(int i=0; i < NEvents; i++){
    RTPEventNotePlus *eventNote = new RTPEventNotePlus(_midiChannel,random(0,100) > 60, random(48,72), random(40,100)); // true, 60, 80
    EventNoteSequence.add(eventNote);
  }
}

void RTPEventNoteSequence::fordwardSequence(){
  _currentPosition++;
  if(_currentPosition >= EventNoteSequence.size()){
    _currentPosition = 0;
  }
}

void RTPEventNoteSequence::backwardSequence(){
  _currentPosition--;
  if(_currentPosition < 0){
    _currentPosition = EventNoteSequence.size();
  }
}

void RTPEventNoteSequence::resetSequence(){
  _currentPosition = 0;
}

int RTPEventNoteSequence::getCurrentSequencePosition(){
  return _currentPosition;
}

bool RTPEventNoteSequence::isCurrentSequenceEnabled(){
  return _isEnabled;
}

int RTPEventNoteSequence::getSequenceType(){
  return _type;
}

RTPEventNotePlus* RTPEventNoteSequence::getCurrentEventNote(){
  if(isCurrentSequenceEnabled() && EventNoteSequence.get(_currentPosition)->eventState())
    return EventNoteSequence.get(_currentPosition);
  else
    return NULL;
}

void RTPEventNoteSequence::setMidiChannel(int midiChannel){
  _midiChannel = midiChannel;
}
int RTPEventNoteSequence::getMidiChannel(){
  return _midiChannel;
}

void RTPEventNoteSequence::editSequenceBlock(LinkedList<RTPEventNote*> displayedEventsList, int NsequenceBlock){
  for (int i=0; i<SEQ_BLOCK_SIZE; i++){
    int currentIndex = NsequenceBlock * SEQ_BLOCK_SIZE + i;
    if(currentIndex <= EventNoteSequence.size()){
      //RTPEventNotePlus eventNote( _midiChannel, displayedEventsList.get(i)->eventState(),
                                  //displayedEventsList.get(i)->getEventNote(), displayedEventsList.get(i)->getEventVelocity() );
      //RTPEventNotePlus* eventNotePointer = &eventNote;
      //EventNoteSequence.set(currentIndex, eventNotePointer);
    }
  }
}

