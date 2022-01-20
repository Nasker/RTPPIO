#include "BuitStateMachine.h"

class GlobalSettingsState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  GlobalSettingsState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void longClick();
  void rotaryTurned(ControlCommand command);
  void threeAxisChanged(ControlCommand command);
  void trellisPressed(ControlCommand command);
  void trellisReleased(ControlCommand command);
};
