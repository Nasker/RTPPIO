#include "VoidStateMachine.h"

class GlobalSettingsState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  GlobalSettingsState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
