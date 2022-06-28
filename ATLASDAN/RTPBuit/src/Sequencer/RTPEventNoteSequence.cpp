#include <RTPEventNoteSequence.h>
#include "RTPEventNotePlus.h"
#include "RTPTypeColors.h"
#include "ReMap.hpp"


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
  _selectedPage = 0;
  _pages = ceil(NEvents / SEQ_BLOCK_SIZE);

  for(int i=0; i < NEvents; i++){
    RTPEventNotePlus eventNote = RTPEventNotePlus(midiChannel, false, _baseNote , 80); // true, 60, 80
    EventNoteSequence.push_back(eventNote);
  }
}

void RTPEventNoteSequence::connectNotesPlayer(const NotesPlayer& notesPlayer){
  _notesPlayer = (NotesPlayer*) &notesPlayer;
}

void RTPEventNoteSequence::connectMusicManager(const MusicManager& musicManager){
  _musicManager = (MusicManager*) &musicManager;
}

void RTPEventNoteSequence::fordwardSequence(){
  _currentPosition++;
  if(_currentPosition >= getSequenceSize())
    _currentPosition = 0;

}

void RTPEventNoteSequence::backwardSequence(){
  _currentPosition--;
  if(_currentPosition < 0)
    _currentPosition = getSequenceSize();
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

void RTPEventNoteSequence::increasePage(){
  _selectedPage++;
  if(_selectedPage >= _pages)
    _selectedPage = _pages - 1;
}

void RTPEventNoteSequence::decreasePage(){
  _selectedPage--;
  if(_selectedPage < 0)
    _selectedPage = 0;
}

int RTPEventNoteSequence::getParameterValue(){
  return sequenceParameters[_selectedParameter].getValue();
}

RTPEventNotePlus* RTPEventNoteSequence::getCurrentEventNote(){
  if(isCurrentSequenceEnabled() && getEventNote(_currentPosition).eventState())
    return &getEventNote(_currentPosition);
  else
    return NULL;
}

void RTPEventNoteSequence::playCurrentEventNote(){
  if(isCurrentSequenceEnabled() && getEventNote(_currentPosition).eventState()){
    switch (getType()){
      case DRUM:{
        getEventNote(_currentPosition).setLength(1);
        _notesPlayer->queueNote(getEventNote(_currentPosition));
        return;
      }
      case BASS_SYNTH:{
        //EventNoteSequence[_currentPosition].setLength(4);
        _musicManager->setCurrentSteps(getEventNote(_currentPosition).getEventRead(), BASS_SYNTH);
        getEventNote(_currentPosition).setEventNote(_musicManager->getCurrentChordNote());
        _notesPlayer->queueNote(getEventNote(_currentPosition));
        return;
      }
      case MONO_SYNTH:
        //EventNoteSequence[_currentPosition].setLength(4);
        _musicManager->setCurrentSteps(getEventNote(_currentPosition).getEventRead(), MONO_SYNTH);
        getEventNote(_currentPosition).setEventNote(_musicManager->getCurrentChordNote());
        _notesPlayer->queueNote(getEventNote(_currentPosition));
        return;
      case POLY_SYNTH:
        //EventNoteSequence[_currentPosition].setLength(16);
        _musicManager->setCurrentSteps(getEventNote(_currentPosition).getEventRead(), POLY_SYNTH);
        auto chordNotes = _musicManager->getCurrentChordNotes();
        while(!chordNotes.empty()){
          getEventNote(_currentPosition).setEventNote(chordNotes.front());
          _notesPlayer->queueNote(getEventNote(_currentPosition));
          chordNotes.pop();
        }
        return;
    }
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

void RTPEventNoteSequence::editNoteInSequence(size_t position, bool eventState){
  position = position + pageOffset();
  if(position < EventNoteSequence.size())
    getEventNote(position).setEventState(eventState);
}

bool RTPEventNoteSequence::getNoteStateInSequence(size_t position){
  position = position + pageOffset();
  if(position < EventNoteSequence.size())
    return getEventNote(position).eventState();
  else
    return false;
}

void RTPEventNoteSequence::editNoteInSequence(size_t position, int note, int velocity){
  position = position + pageOffset();
  if(position < EventNoteSequence.size()){
    getEventNote(position).setEventNote(note);
    getEventNote(position).setEventVelocity(velocity);
  }
}

void RTPEventNoteSequence::editNoteInCurrentPosition(ControlCommand command){
  if(command.controlType == THREE_AXIS){ 
    switch(command.commandType){
      case CHANGE_LEFT:{
        if (getType()!= DRUM)
          getEventNote(_currentPosition).setEventRead(command.value);
        return;
      }
      case CHANGE_RIGHT:{
        getEventNote(_currentPosition).setEventVelocity(command.value);
        return;
      }
      case CHANGE_CENTER:{
        if (getType()!= DRUM)
          getEventNote(_currentPosition).setLength(remap(command.value, 0, 127, 1, 16));
        return;
      }
    } 
  }
}

void RTPEventNoteSequence::resizeSequence(size_t newSize){
  if(newSize > EventNoteSequence.size()){
    for(size_t i=EventNoteSequence.size(); i < newSize; i++){
      RTPEventNotePlus eventNote = RTPEventNotePlus(sequenceParameters[MIDI_CHANNEL].getValue(),false, 60, 80);
      EventNoteSequence.push_back(eventNote);
    }
  }
  else if(newSize < EventNoteSequence.size()){
    while(EventNoteSequence.size() > newSize)
      EventNoteSequence.pop_back();
  }
}

int RTPEventNoteSequence::pageOffset(){
  return _selectedPage * SEQ_BLOCK_SIZE;
}

list<RTPEventNotePlus> RTPEventNoteSequence::getEventNoteSequence(){
  return EventNoteSequence;
}

String RTPEventNoteSequence::dumpSequenceToJson(){
  String noteSeqString;
  StaticJsonDocument<1536> doc;
  doc["type"] = getType();
  doc["ch"] = getMidiChannel();
  JsonArray seq = doc.createNestedArray("seq");
  for (RTPEventNotePlus eventNote : EventNoteSequence){
    JsonObject note = seq.createNestedObject();
    note["read"] = eventNote.getEventRead();
    note["vel"] = eventNote.eventState() ? eventNote.getEventVelocity() : 0;
    note["len"] = eventNote.getLength();
  }
  serializeJsonPretty(doc, noteSeqString);
  Serial.printf("%s\n", noteSeqString.c_str());
  return noteSeqString;
}

RTPEventNotePlus RTPEventNoteSequence::getEventNote(int position){
  it = EventNoteSequence.begin();
  advance(it, position);
  return *it;
}