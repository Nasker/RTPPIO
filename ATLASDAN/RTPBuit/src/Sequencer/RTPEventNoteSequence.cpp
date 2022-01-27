#include <RTPEventNoteSequence.h>
#include "RTPEventNotePlus.h"
#include "RTPTypeColors.h"


RTPEventNoteSequence::RTPEventNoteSequence(int midiChannel, int NEvents, int type, int baseNote){
  RTPParameter *parameterType = new RTPParameter(0,2,type);
  RTPParameter *parameterMidiChannel = new RTPParameter(1,16,midiChannel);
  RTPParameter *parameterColor = new RTPParameter(0,0XFFFFFF,0);
  sequenceParameters.add(parameterType);
  sequenceParameters.add(parameterMidiChannel);
  sequenceParameters.add(parameterColor);
  switch (getType()){
    case DRUM:
      setColor(DRUM_COLOR);
      break;
    case BASS_SYNTH:
      setColor(BASS_SYNTH_COLOR);
      break;
    case MONO_SYNTH:
      setColor(MONO_SYNTH_COLOR);
      break;
    case POLY_SYNTH:
      setColor(POLY_SYNTH_COLOR);
      break;
  }
  _baseNote = baseNote;
  _currentPosition = 0;
  _isRecording = false;
  _isEnabled = true;
  _selectedParameter = 0;

  for(int i=0; i < NEvents; i++){
    RTPEventNotePlus *eventNote = new RTPEventNotePlus(midiChannel, false, _baseNote , 80); // true, 60, 80
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

void RTPEventNoteSequence::enableSequence(bool state){
  _isEnabled = state;
}

void RTPEventNoteSequence::selectParameter(int parameterIndex){
  _selectedParameter = parameterIndex;
}

void RTPEventNoteSequence::increaseParameterValue(){
  sequenceParameters.get(_selectedParameter)->incValue();
}

void RTPEventNoteSequence::decreaseParameterValue(){
  sequenceParameters.get(_selectedParameter)->decValue();
}

int RTPEventNoteSequence::getParameterValue(){
  return sequenceParameters.get(_selectedParameter)->getValue();
}

RTPEventNotePlus* RTPEventNoteSequence::getCurrentEventNote(){
  if(isCurrentSequenceEnabled() && EventNoteSequence.get(_currentPosition)->eventState())
    return EventNoteSequence.get(_currentPosition);
  else
    return NULL;
}

void RTPEventNoteSequence::setMidiChannel(int midiChannel){
  sequenceParameters.get(MIDI_CHANNEL)->setValue(midiChannel);
}

int RTPEventNoteSequence::getMidiChannel(){
  return sequenceParameters.get(MIDI_CHANNEL)->getValue();
}

void RTPEventNoteSequence::setColor(int color){
  sequenceParameters.get(COLOR)->setValue(color);
}
	
int RTPEventNoteSequence::getColor(){
  return sequenceParameters.get(COLOR)->getValue();
}

void RTPEventNoteSequence::setType(int type){
  sequenceParameters.get(TYPE)->setValue(type);
}
int RTPEventNoteSequence::getType(){
  return sequenceParameters.get(TYPE)->getValue();
}

int RTPEventNoteSequence::getSequenceSize(){
  return EventNoteSequence.size();
}

void RTPEventNoteSequence::editNoteInSequence(int position, bool eventState){
  if(position < EventNoteSequence.size()){
    EventNoteSequence.get(position)->setEventState(eventState);
  }
}

bool RTPEventNoteSequence::getNoteStateInSequence(int position){
  if(position < EventNoteSequence.size()){
    return EventNoteSequence.get(position)->eventState();
  }
  else{
    return false;
  }
}

void RTPEventNoteSequence::editNoteInSequence(int position, int note, int velocity){
  if(position < EventNoteSequence.size()){
    EventNoteSequence.get(position)->setEventNote(note);
    EventNoteSequence.get(position)->setEventVelocity(velocity);
  }
}

void RTPEventNoteSequence::resizeSequence(int newSize){
  if(newSize > EventNoteSequence.size()){
    for(int i=EventNoteSequence.size(); i < newSize; i++){
      RTPEventNotePlus *eventNote = new RTPEventNotePlus(sequenceParameters.get(MIDI_CHANNEL)->getValue(),false, 60, 80);
      EventNoteSequence.add(eventNote);
    }
  }
  else if(newSize < EventNoteSequence.size()){
    for(int i=EventNoteSequence.size(); i > newSize; i--){
      EventNoteSequence.remove(i);
    }
  }
}