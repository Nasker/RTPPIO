#include "RTPSequencer.h"
#include <iostream>

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
          //playNoteOn(Sequencer.get(i)->getPlayedNotesList().get(j));
          Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOn();
          Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOff();
          Sequencer.get(i)->getPlayedNotesList().remove(j);
          playNoteOff(Sequencer.get(i)->getPlayedNotesList().get(j));
          break;
        case SYNTH:
          Sequencer.get(i)->getPlayedNotesList().get(j)->playNoteOn();
          //playNoteOn(Sequencer.get(i)->getPlayedNotesList().get(j));
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

void RTPSequencer::editSceneSequenceBlock(int scene, int sequence, LinkedList<RTPEventNote*> displayedEventsList, int NsequenceBlock){
  Sequencer.get(scene)->editSceneSequenceBlock(sequence, displayedEventsList, NsequenceBlock);
}


void RTPSequencer::playNoteOn(RTPEventNotePlus* eventNote) {
    //usbMIDI.sendNoteOn(eventNote->getEventNote(), eventNote->getEventVelocity(), eventNote->getMidiChannel());
    //MIDI.sendNoteOn(midiNote, velocity, channel);
}

void RTPSequencer::playNoteOff(RTPEventNotePlus* eventNote) {
    //usbMIDI.sendNoteOff(eventNote->getEventNote(), eventNote->getEventVelocity(), eventNote->getMidiChannel());
    //MIDI.sendNoteOff(midiNote, velocity, channel);
    //Serial.println("SEND_NOTE OFF");
}
