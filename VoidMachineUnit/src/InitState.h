#include "VoidStateMachine.h"

class InitState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  InitState(VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
