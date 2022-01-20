#include "VoidStateMachine.h"

class SceneSettingsState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SceneSettingsState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
