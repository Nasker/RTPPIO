#include "BuitStateMachine.h"

class SceneSettingsState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  SceneSettingsState (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void longClick();
  void rotaryTurned(ControlCommand command);
  void threeAxisChanged(ControlCommand command);
  void trellisPressed(ControlCommand command);
  void trellisReleased(ControlCommand command);
};
