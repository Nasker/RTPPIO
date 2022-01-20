#include "VoidStateMachine.h"

class SceneEditState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SceneEditState(BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
