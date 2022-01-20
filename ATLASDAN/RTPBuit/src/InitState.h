#include "BuitStateMachine.h"

class InitState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  InitState(BuitStateMachine* buitMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
