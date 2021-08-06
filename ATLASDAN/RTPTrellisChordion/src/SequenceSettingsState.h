#include "VoidStateMachine.h"

class SequenceSettingsState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  SequenceSettingsState (VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
