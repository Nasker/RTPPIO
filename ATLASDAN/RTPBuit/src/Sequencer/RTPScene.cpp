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
    RTPEventNoteSequence *sequence = new RTPEventNoteSequence(midiChannels[i], SEQ_BLOCK_SIZE, types[i], baseNote);
    SequencerScene.add(sequence);
  }
}

void RTPScene::fordwardScene(){
  for(int i=0; i<SequencerScene.size(); i++)
    SequencerScene.get(i)->fordwardSequence();
}

void RTPScene::backwardScene(){
  for(int i=0; i<SequencerScene.size(); i++)
    SequencerScene.get(i)->backwardSequence();
}

void RTPScene::resetScene(){
  for(int i=0; i<SequencerScene.size(); i++)
    SequencerScene.get(i)->resetSequence();
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
    if(i < SequencerScene.get(_selectedSequence)->getSequenceSize())
      _seqStates.val[i] = SequencerScene.get(_selectedSequence)->getNoteStateInSequence(i);
    else
      _seqStates.val[i] = false;
  } 
  return _seqStates;
}

RTPSequencesState RTPScene::getSequencesState(){
  RTPSequencesState seqsState;
  for(int i=0; i<SequencerScene.size(); i++){
    seqsState.sequenceState[i].state = SequencerScene.get(i)->isCurrentSequenceEnabled();
    seqsState.sequenceState[i].color = SequencerScene.get(i)->getColor();
  }
  return seqsState;
}

int RTPScene::getSequenceType(int sequenceIndex)  {
  return SequencerScene.get(sequenceIndex)->getType();
}

void RTPScene::selectParameterInSequece(int parameterIndex){
  SequencerScene.get(_selectedSequence)->selectParameter(parameterIndex);
}

void RTPScene::incselectParameterInSequece(){
  SequencerScene.get(_selectedSequence)->increaseParameterValue();
}

void RTPScene::decselectParameterInSequece(){
  SequencerScene.get(_selectedSequence)->decreaseParameterValue();
}

int RTPScene::getSelectedParameterInSequeceValue(){
  return SequencerScene.get(_selectedSequence)->getParameterValue();
}

void RTPScene::toggleSequence(int sequenceIndex){
  SequencerScene.get(sequenceIndex)->enableSequence(!SequencerScene.get(sequenceIndex)->isCurrentSequenceEnabled());
  //Serial.printf("Sequence %d is %s\n", sequenceIndex, SequencerScene.get(sequenceIndex)->isCurrentSequenceEnabled() ? "enabled" : "disabled");
}

void RTPScene::toggleNoteInSequence(int position){
  SequencerScene.get(_selectedSequence)->editNoteInSequence(position,
  !SequencerScene.get(_selectedSequence)->getNoteStateInSequence(position));
}

LinkedList<RTPEventNotePlus*>  RTPScene::getPlayedNotesList(){
  LinkedList <RTPEventNotePlus*> playedNotesList = LinkedList<RTPEventNotePlus*>();
  for(int i=0; i<SequencerScene.size(); i++){
    if(SequencerScene.get(i)->getCurrentEventNote() != NULL)
      playedNotesList.add(SequencerScene.get(i)->getCurrentEventNote());
  }
  return playedNotesList;
}

RTPSequenceNoteStates RTPScene::getSequenceNoteStates(){
  for(int i=0; i<SequencerScene.get(_selectedSequence)->getSequenceSize(); i++){
    _seqStates.val[i] = SequencerScene.get(_selectedSequence)->getNoteStateInSequence(i);
  }
  return _seqStates;
}

int RTPScene::getSequenceColor(){
  return SequencerScene.get(_selectedSequence)->getColor();
}
