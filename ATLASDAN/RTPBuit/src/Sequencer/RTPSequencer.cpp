#include "RTPSequencer.h"

RTPSequencer::RTPSequencer(int NScenes){
  Serial.println("CREATING RTPSequencer");
  _NScenes = NScenes;
  _selectedScene = 0;
  for(int i=0; i < _NScenes; i++){
    RTPScene *scene = new RTPScene("Scene", SCENE_BLOCK_SIZE);
    Sequencer.add(scene);
  }
}

void RTPSequencer::playAndMoveSequencer(){
  for(int i=0; i<Sequencer.size(); i++){
    for(int j=0; j<Sequencer.get(i)->getPlayedNotesList().size(); j++){
      switch(Sequencer.get(i)->getSequenceType(j)){
        case DRUM: 
          Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOn();
          Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOff();
          Sequencer.get(i)->getPlayedNotesList().remove(j);
          
          break;
        case MONO_SYNTH:
          Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOn();
          break;
      }
    }
    Sequencer.get(i)->fordwardScene();
  }
}

void RTPSequencer::stopAndCleanSequencer(){
  for(int i=0; i<Sequencer.size(); i++){
    Sequencer.get(i)->resetScene();
    for(int j=0; j<Sequencer.get(i)->getPlayedNotesList().size(); j++){
      Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOff();
      Sequencer.get(i)->getPlayedNotesList().remove(j);
    }
  }
}

void RTPSequencer::pauseSequencer(){
  for(int i=0; i<Sequencer.size(); i++){
    for(int j=0; j<Sequencer.get(i)->getPlayedNotesList().size(); j++){
      Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOff();
      Sequencer.get(i)->getPlayedNotesList().remove(j);
    }
  }
}

void RTPSequencer::selectScene(int scene){
  _selectedScene = scene;
}

int RTPSequencer::getSelectScene(){
  return _selectedScene;
}

void RTPSequencer::addScene(RTPScene* scene){
  Sequencer.add(scene);
}

void RTPSequencer::removeScene(int scene){
  Sequencer.remove(scene);
}

void RTPSequencer::toggleNoteInSceneInSelectedSequence(int position){
  Sequencer.get(_selectedScene)->toggleNoteInSequence(position);
}

void RTPSequencer::toggleSequence(int sequenceIndex){
  Sequencer.get(_selectedScene)->toggleSequence(sequenceIndex);
}

RTPSequencesState RTPSequencer::getSequencesState(){
  RTPSequencesState sequencesState = Sequencer.get(_selectedScene)->getSequencesState();
  return sequencesState;
}

void RTPSequencer::selectSequence(int sequenceIndex){
  Sequencer.get(_selectedScene)->setSelectedSequence(sequenceIndex);
}

RTPSequenceNoteStates RTPSequencer::getSelectedSequenceNoteStates(){
  RTPSequenceNoteStates sequenceNoteStates = Sequencer.get(_selectedScene)->getSequenceNoteStates();
  return sequenceNoteStates;
}

int RTPSequencer::getSelectedSequenceColor(){
  return Sequencer.get(_selectedScene)->getSequenceColor();
}