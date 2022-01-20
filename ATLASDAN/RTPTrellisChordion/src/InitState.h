#include "VoidStateMachine.h"

class InitState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  InitState(BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
