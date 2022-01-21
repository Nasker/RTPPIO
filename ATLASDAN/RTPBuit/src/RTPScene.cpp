#include <RTPScene.h>

RTPScene::RTPScene(String name, int NSequences){
  _name = name;
  _NSequences = NSequences;
  for(int i=0; i < _NSequences; i++){
    RTPEventNoteSequence *sequence = new RTPEventNoteSequence(i, 16, DRUM);
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
