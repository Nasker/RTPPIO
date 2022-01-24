#include "BuitStateMachine.h"

class SequenceEditState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SequenceEditState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void longClick();
  void rotaryTurned(ControlCommand command);
  void threeAxisChanged(ControlCommand command);
  void trellisPressed(ControlCommand command);
  void trellisReleased(ControlCommand command);
};
