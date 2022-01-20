#include "VoidStateMachine.h"

class SequenceSettingsState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SequenceSettingsState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
