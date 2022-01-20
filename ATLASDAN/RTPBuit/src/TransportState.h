#include "BuitStateMachine.h"

class TransportState : public BuitState{
  BuitStateMachine* _buitMachine;
public:
  TransportState  (BuitStateMachine* buitMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
