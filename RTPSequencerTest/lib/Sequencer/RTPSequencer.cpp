#include "RTPSequencer.h"

RTPSequencer::RTPSequencer(int NScenes){
  _NScenes = NScenes;
  for(int i=0; i < _NScenes; i++){
    RTPScene *scene = new RTPScene("Scene", 16);
    Sequencer.add(scene);
  }
}
