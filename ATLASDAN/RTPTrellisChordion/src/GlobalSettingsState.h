#include "VoidStateMachine.h"

class GlobalSettingsState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  GlobalSettingsState (VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
