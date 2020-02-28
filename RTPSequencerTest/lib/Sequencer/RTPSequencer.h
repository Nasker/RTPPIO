#include <LinkedList.h>
#include <RTPScene.h>
#include "Arduino.h"

class RTPSequencer{
  LinkedList<RTPScene*> Sequencer = LinkedList<RTPScene*>();
  int _NScenes;
public:
    RTPSequencer(int NScenes);
};
