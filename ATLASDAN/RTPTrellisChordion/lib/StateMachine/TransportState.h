#include "VoidStateMachine.h"

class TransportState : public VoidState{
  VoidStateMachine* _voidMachine;
public:
  TransportState  (VoidStateMachine* voidMachine);
  void singleClick();
  void doubleClick();
  void tripleClick();
  void longClick();
};
