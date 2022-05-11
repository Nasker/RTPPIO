#include "RTPSequencer.h"

RTPSequencer::RTPSequencer(int NScenes){
  Serial.println("CREATING RTPSequencer");
  _NScenes = NScenes;
  _selectedScene = 0;
  for(int i=0; i < _NScenes; i++){
    RTPScene scene = RTPScene("Scene", SCENE_BLOCK_SIZE);
    Sequencer.push_back(scene);
    Sequencer[i].connectNotesPlayer(_notesPlayer);
  }
}
 
void RTPSequencer::playAndMoveSequencer(){
  for(int i=0; i<Sequencer.size(); i++){ 
    Sequencer[i].playScene();
    _notesPlayer.playNotes();
    Sequencer[i].fordwardScene();
    _notesPlayer.decreaseTimeToLive();
  }
}

void RTPSequencer::stopAndCleanSequencer(){
  for(int i=0; i<Sequencer.size(); i++)
    Sequencer[i].resetScene();
  _notesPlayer.killAllNotes();
}

void RTPSequencer::pauseSequencer(){
  _notesPlayer.killAllNotes();
}

void RTPSequencer::selectScene(int scene){
  _selectedScene = scene;
}

int RTPSequencer::getSelectScene(){
  return _selectedScene;
}

void RTPSequencer::addScene(RTPScene scene){
  Sequencer.push_back(scene);
}

void RTPSequencer::removeScene(int scene){
  //Sequencer.remove(scene);
}

void RTPSequencer::toggleNoteInSceneInSelectedSequence(int position){
  Sequencer[_selectedScene].toggleNoteInSequence(position);
}

void RTPSequencer::toggleSequence(int sequenceIndex){
  Sequencer[_selectedScene].toggleSequence(sequenceIndex);
}

RTPSequencesState RTPSequencer::getSequencesState(){
  RTPSequencesState sequencesState = Sequencer[_selectedScene].getSequencesState();
  return sequencesState;
}

void RTPSequencer::selectSequence(int sequenceIndex){
  Sequencer[_selectedScene].setSelectedSequence(sequenceIndex);
}

RTPSequenceNoteStates RTPSequencer::getSelectedSequenceNoteStates(){
  RTPSequenceNoteStates sequenceNoteStates = Sequencer[_selectedScene].getSequenceNoteStates();
  return sequenceNoteStates;
}

void RTPSequencer::editNoteInCurrentPosition(ControlCommand command){
  Sequencer[_selectedScene].editNoteInCurrentPosition(command);
}

int RTPSequencer::getSelectedSequenceColor(){
  return Sequencer[_selectedScene].getSequenceColor();
}