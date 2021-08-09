#include <RTPScene.h>

RTPScene::RTPScene(std::string name, int NSequences){
  _name = name;
  _NSequences = NSequences;
  for(int i=0; i < _NSequences; i++){
    RTPEventNoteSequence *sequence = new RTPEventNoteSequence(i, 16, "DRUM");
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
  return SequencerScene.get(sequenceIndex)->getSequenceType();
}

LinkedList<RTPEventNotePlus*>  RTPScene::getPlayedNotesList(){
  LinkedList <RTPEventNotePlus*> playedNotesList = LinkedList<RTPEventNotePlus*>();
  for(int i=0; i<SequencerScene.size(); i++){
    if(SequencerScene.get(i)->getCurrentEventNote() != NULL)
      playedNotesList.add(SequencerScene.get(i)->getCurrentEventNote());
  }
  return playedNotesList;
}

void RTPScene::editSceneSequenceBlock(int sequence, LinkedList<RTPEventNote*> displayedEventsList, int NsequenceBlock){
  SequencerScene.get(sequence)->editSequenceBlock(displayedEventsList, NsequenceBlock);
}
