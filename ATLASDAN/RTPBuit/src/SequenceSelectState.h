#include "BuitStateMachine.h"

class SequenceSelectState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SequenceSelectState(BuitStateMachine* buitMachine);
  void singleClick();
  void doubleClick();
  void longClick();
  void rotaryTurned(ControlCommand command);
  void threeAxisChanged(ControlCommand command);
  void trellisPressed(ControlCommand command);
  void trellisReleased(ControlCommand command);
};
