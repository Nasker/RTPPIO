#include "VoidStateMachine.h"

class TransportState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  TransportState  (BuitStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
