#include <RTPScene.h>

RTPScene::RTPScene(String name, int NSequences){
  _name = name;
  _NSequences = NSequences;
  for(int i=0; i < _NSequences; i++){
    RTPEventNoteSequence *sequence = new RTPEventNoteSequence(i, 16, "DRUM");
    SequencerScene.add(sequence);
  }
}
