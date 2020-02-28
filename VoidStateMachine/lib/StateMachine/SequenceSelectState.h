#include "VoidStateMachine.h"

class SequenceSelectState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  SequenceSelectState(VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
