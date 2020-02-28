#include "VoidStateMachine.h"

class SceneEditState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  SceneEditState(VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
