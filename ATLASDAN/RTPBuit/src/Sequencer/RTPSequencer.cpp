#include "RTPSequencer.h"

RTPSequencer::RTPSequencer(int NScenes){
  Serial.println("CREATING RTPSequencer");
  _NScenes = NScenes;
  _selectedScene = 0;
  for(int i=0; i < _NScenes; i++){
    RTPScene scene = RTPScene("Scene", SCENE_BLOCK_SIZE);
    Sequencer.push_back(scene);
  }
}

void RTPSequencer::playAndMoveSequencer(){
  for(int i=0; i<Sequencer.size(); i++){
    for(int j=0; j<Sequencer[i].getPlayedNotesList().size(); j++){
      switch(Sequencer[i].getSequenceType(j)){
        case DRUM: 
          Sequencer[i].getPlayedNotesList().get(j)->playNoteOn();
          Sequencer[i].getPlayedNotesList().get(j)->playNoteOff();
          Sequencer[i].getPlayedNotesList().remove(j);
          
          break;
        case MONO_SYNTH:
          Sequencer[i].getPlayedNotesList().get(i)->playNoteOn();
          break;
      }
    }
    Sequencer[i].fordwardScene();
  }
}

void RTPSequencer::stopAndCleanSequencer(){
  for(int i=0; i<Sequencer.size(); i++){
    Sequencer[i].resetScene();
    for(int j=0; j<Sequencer[i].getPlayedNotesList().size(); j++){
      Sequencer[i].getPlayedNotesList().get(j)->playNoteOff();
      Sequencer[i].getPlayedNotesList().remove(j);
    }
  }
}

void RTPSequencer::pauseSequencer(){
  for(int i=0; i<Sequencer.size(); i++){
    for(int j=0; j<Sequencer[i].getPlayedNotesList().size(); j++){
      Sequencer[i].getPlayedNotesList().get(j)->playNoteOff();
      Sequencer[i].getPlayedNotesList().remove(j);
    }
  }
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

int RTPSequencer::getSelectedSequenceColor(){
  return Sequencer[_selectedScene].getSequenceColor();
}