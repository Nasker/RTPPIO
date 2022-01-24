#include "BuitStateMachine.h"

class InitState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  InitState(BuitStateMachine* buitMachine);
  void singleClick();
  void doubleClick();
  void longClick();
  void rotaryTurned(ControlCommand command);
  void threeAxisChanged(ControlCommand command);
  void trellisPressed(ControlCommand command);
  void trellisReleased(ControlCommand command);
};
