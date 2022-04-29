#include <RTPScene.h>

int types[16] = {
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  DRUM,
  BASS_SYNTH,
  MONO_SYNTH,
  POLY_SYNTH,
  POLY_SYNTH
};

int midiChannels[16] = {
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  1,
  2,
  3,
  4
};

RTPScene::RTPScene(String name, int NSequences){
  _name = name;
  _NSequences = NSequences;
  _selectedSequence = 0;
  for(int i=0; i < _NSequences; i++){
    int baseNote = types[i] == DRUM ? 36 + i : 60;
    RTPEventNoteSequence sequence = RTPEventNoteSequence(midiChannels[i], SEQ_BLOCK_SIZE, types[i], baseNote);
    SequencerScene.push_back(sequence);
  }
}

void RTPScene::playScene(){
  for(int i=0; i<SequencerScene.size(); i++)
    SequencerScene[i].playCurrentEventNote();
}

void RTPScene::fordwardScene(){
  for(int i=0; i<SequencerScene.size(); i++)
    SequencerScene[i].fordwardSequence();
}

void RTPScene::backwardScene(){
  for(int i=0; i<SequencerScene.size(); i++)
    SequencerScene[i].backwardSequence();
}

void RTPScene::resetScene(){
  for(int i=0; i<SequencerScene.size(); i++)
    SequencerScene[i].resetSequence();
}

void RTPScene::setSelectedSequence(int selectedSequence){
  _selectedSequence = selectedSequence;
}

int RTPScene::getSelectedSequence(){
  return _selectedSequence;
}

int RTPScene::getSize(){
  return SequencerScene.size();
}

RTPSequenceNoteStates RTPScene::getSelectedSequenceNoteStates(){
  for(int i=0; i<SEQ_BLOCK_SIZE; i++){
    if(i < SequencerScene[_selectedSequence].getSequenceSize())
      _seqStates.val[i] = SequencerScene[_selectedSequence].getNoteStateInSequence(i);
    else
      _seqStates.val[i] = false;
  } 
  return _seqStates;
}

RTPSequencesState RTPScene::getSequencesState(){
  RTPSequencesState seqsState;
  for(int i=0; i<SequencerScene.size(); i++){
    seqsState.sequenceState[i].state = SequencerScene[i].isCurrentSequenceEnabled();
    seqsState.sequenceState[i].color = SequencerScene[i].getColor();
  }
  return seqsState;
}

int RTPScene::getSequenceType(int sequenceIndex)  {
  return SequencerScene[sequenceIndex].getType();
}

void RTPScene::selectParameterInSequece(int parameterIndex){
  SequencerScene[_selectedSequence].selectParameter(parameterIndex);
}

void RTPScene::incselectParameterInSequece(){
  SequencerScene[_selectedSequence].increaseParameterValue();
}

void RTPScene::decselectParameterInSequece(){
  SequencerScene[_selectedSequence].decreaseParameterValue();
}

int RTPScene::getSelectedParameterInSequeceValue(){
  return SequencerScene[_selectedSequence].getParameterValue();
}

void RTPScene::toggleSequence(int sequenceIndex){
  SequencerScene[sequenceIndex].enableSequence(!SequencerScene[sequenceIndex].isCurrentSequenceEnabled());
  //Serial.printf("Sequence %d is %s\n", sequenceIndex, SequencerScene.get(sequenceIndex)->isCurrentSequenceEnabled() ? "enabled" : "disabled");
}

void RTPScene::toggleNoteInSequence(int position){
  SequencerScene[_selectedSequence].editNoteInSequence(position,
  !SequencerScene[_selectedSequence].getNoteStateInSequence(position));
}
/*
LinkedList<RTPEventNotePlus*>  RTPScene::getPlayedNotesList(){
  LinkedList <RTPEventNotePlus*> playedNotesList = LinkedList<RTPEventNotePlus*>();
  for(int i=0; i<SequencerScene.size(); i++){
    if(SequencerScene[i].getCurrentEventNote() != NULL)
      playedNotesList.add(SequencerScene[i].getCurrentEventNote());

  }
  return playedNotesList;
}*/

RTPSequenceNoteStates RTPScene::getSequenceNoteStates(){
  for(int i=0; i<SequencerScene[_selectedSequence].getSequenceSize(); i++){
    _seqStates.val[i] = SequencerScene[_selectedSequence].getNoteStateInSequence(i);
  }
  return _seqStates;
}

int RTPScene::getSequenceColor(){
  return SequencerScene[_selectedSequence].getColor();
}