#include "BuitStateMachine.h"

class SequencePianoRollState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SequencePianoRollState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
