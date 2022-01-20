#include "BuitStateMachine.h"

class SequenceSettingsState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SequenceSettingsState (BuitStateMachine* buitMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
