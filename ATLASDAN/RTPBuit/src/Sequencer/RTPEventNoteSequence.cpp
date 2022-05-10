#include <RTPEventNoteSequence.h>
#include "RTPEventNotePlus.h"
#include "RTPTypeColors.h"


RTPEventNoteSequence::RTPEventNoteSequence(int midiChannel, int NEvents, int type, int baseNote){
  RTPParameter parameterType = RTPParameter(0,2,type);
  RTPParameter parameterMidiChannel = RTPParameter(1,16,midiChannel);
  RTPParameter parameterColor = RTPParameter(0,0XFFFFFF,0);
  sequenceParameters.push_back(parameterType);
  sequenceParameters.push_back(parameterMidiChannel);
  sequenceParameters.push_back(parameterColor);
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
    RTPEventNotePlus eventNote = RTPEventNotePlus(midiChannel, false, _baseNote , 80); // true, 60, 80
    EventNoteSequence.push_back(eventNote);
  }
}

void RTPEventNoteSequence::connectNotesPlayer(const NotesPlayer& notesPlayer){
  _notesPlayer = (NotesPlayer*) &notesPlayer;
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
  sequenceParameters[_selectedParameter].incValue();
}

void RTPEventNoteSequence::decreaseParameterValue(){
  sequenceParameters[_selectedParameter].decValue();
}

int RTPEventNoteSequence::getParameterValue(){
  return sequenceParameters[_selectedParameter].getValue();
}

RTPEventNotePlus* RTPEventNoteSequence::getCurrentEventNote(){
  if(isCurrentSequenceEnabled() && EventNoteSequence[_currentPosition].eventState())
    return &EventNoteSequence[_currentPosition];
  else
    return NULL;
}

void RTPEventNoteSequence::playCurrentEventNote(){
  if(isCurrentSequenceEnabled() && EventNoteSequence[_currentPosition].eventState()){
    _notesPlayer->queueNote(EventNoteSequence[_currentPosition]);
    /*
    switch (getType()){
      case DRUM:
        EventNoteSequence[_currentPosition].playNoteOn();
        EventNoteSequence[_currentPosition].playNoteOff();
        break;
      case BASS_SYNTH:
        EventNoteSequence[_currentPosition].playNoteOff();
        EventNoteSequence[_currentPosition].playNoteOn();
        break;
      case MONO_SYNTH:
        EventNoteSequence[_currentPosition].playNoteOff();
        EventNoteSequence[_currentPosition].playNoteOn();
        break;
      case POLY_SYNTH:
        EventNoteSequence[_currentPosition].playNoteOff();
        EventNoteSequence[_currentPosition].playNoteOn();
        break;
    }*/
  }
}

void RTPEventNoteSequence::setMidiChannel(int midiChannel){
  sequenceParameters[MIDI_CHANNEL].setValue(midiChannel);
}

int RTPEventNoteSequence::getMidiChannel(){
  return sequenceParameters[MIDI_CHANNEL].getValue();
}

void RTPEventNoteSequence::setColor(int color){
  sequenceParameters[COLOR].setValue(color);
}
	
int RTPEventNoteSequence::getColor(){
  return sequenceParameters[COLOR].getValue();
}

void RTPEventNoteSequence::setType(int type){
  sequenceParameters[TYPE].setValue(type);
}
int RTPEventNoteSequence::getType(){
  return sequenceParameters[TYPE].getValue();
}

int RTPEventNoteSequence::getSequenceSize(){
  return EventNoteSequence.size();
}

void RTPEventNoteSequence::editNoteInSequence(int position, bool eventState){
  if(position < EventNoteSequence.size()){
    EventNoteSequence[position].setEventState(eventState);
  }
}

bool RTPEventNoteSequence::getNoteStateInSequence(int position){
  if(position < EventNoteSequence.size()){
    return EventNoteSequence[position].eventState();
  }
  else{
    return false;
  }
}

void RTPEventNoteSequence::editNoteInSequence(int position, int note, int velocity){
  if(position < EventNoteSequence.size()){
    EventNoteSequence[position].setEventNote(note);
    EventNoteSequence[position].setEventVelocity(velocity);
  }
}

void RTPEventNoteSequence::resizeSequence(int newSize){
  if(newSize > EventNoteSequence.size()){
    for(int i=EventNoteSequence.size(); i < newSize; i++){
      RTPEventNotePlus eventNote = RTPEventNotePlus(sequenceParameters[MIDI_CHANNEL].getValue(),false, 60, 80);
      EventNoteSequence.push_back(eventNote);
    }
  }
  else if(newSize < EventNoteSequence.size()){
    while(EventNoteSequence.size() > newSize){
      EventNoteSequence.pop_back();
    }
  }
}