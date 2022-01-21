#include "RTPSequencer.h"

RTPSequencer::RTPSequencer(int NScenes){
  _NScenes = NScenes;
  for(int i=0; i < _NScenes; i++){
    RTPScene *scene = new RTPScene("Scene", 16);
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
