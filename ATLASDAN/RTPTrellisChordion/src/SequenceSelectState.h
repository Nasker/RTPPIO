#include "VoidStateMachine.h"

class SequenceSelectState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SequenceSelectState(BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
