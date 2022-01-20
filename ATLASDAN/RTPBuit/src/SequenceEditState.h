#include "BuitStateMachine.h"

class SequenceEditState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SequenceEditState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
