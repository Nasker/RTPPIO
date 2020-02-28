#include "VoidStateMachine.h"

class SequenceEditState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  SequenceEditState (VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
