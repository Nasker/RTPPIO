#include "VoidStateMachine.h"

class SequencePianoRollState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  SequencePianoRollState (VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
