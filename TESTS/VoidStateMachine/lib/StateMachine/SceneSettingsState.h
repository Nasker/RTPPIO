#include "VoidStateMachine.h"

class SceneSettingsState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  SceneSettingsState (VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
