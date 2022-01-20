#include "BuitStateMachine.h"

class SceneEditState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SceneEditState(BuitStateMachine* buitMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
