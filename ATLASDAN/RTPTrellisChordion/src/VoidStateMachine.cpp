#include "VoidStateMachine.h"
#include "InitState.h"
#include "GlobalSettingsState.h"
#include "TransportState.h"
#include "SceneEditState.h"
#include "SceneSettingsState.h"
#include "SequenceEditState.h"
#include "SequencePianoRollState.h"
#include "SequenceSelectState.h"
#include "SequenceSettingsState.h"

#include "Arduino.h"

BuitStateMachine::BuitStateMachine(){ //, LiquidScreen& lScreen
  _state = new InitState(this);
	_initState = new InitState(this);
	_transportState = new TransportState(this);
	_globalSettingsState = new GlobalSettingsState(this);
	_sceneEditState = new SceneEditState(this);
	_sceneSettingsState = new SceneSettingsState(this);
	_sequenceEditState = new SequenceEditState(this);
	_sequencePianoRollState = new SequencePianoRollState(this);
	_sequenceSelectState = new SequenceSelectState(this);
	_sequenceSettingsState = new SequenceSettingsState(this);
}

void BuitStateMachine::singleClick(){
  _state->singleClick();
}

void BuitStateMachine::doubleClick(){
  _state->doubleClick();
}

void BuitStateMachine::tripleClick(){
  _state->tripleClick();
}

void BuitStateMachine::longClick(){
  _state->longClick();
}

void BuitStateMachine::setState(BuitState* state){
  _state = state;
}

BuitState* BuitStateMachine::getInitState(){
  return _initState;
}

BuitState* BuitStateMachine::getTransportState(){
  return _transportState;
}

BuitState* BuitStateMachine::getGlobalSettingsState(){
  return _globalSettingsState;
}

BuitState* BuitStateMachine::getSceneEditState(){
  return _sceneEditState;
}

BuitState* BuitStateMachine::getSceneSettingsState(){
  return _sceneSettingsState;
}

BuitState* BuitStateMachine::getSequenceEditState(){
  return _sequenceEditState;
}

BuitState* BuitStateMachine::getSequencePianoRollState(){
  return _sequencePianoRollState;
}

BuitState* BuitStateMachine::getSequenceSelectState(){
  return _sequenceSelectState;
}

BuitState* BuitStateMachine::getSequenceSettingsState(){
  return _sequenceSettingsState;
}

void BuitStateMachine::connectScreen(const RTPScreen& screen){
	_initState->connectScreen(screen);
	_transportState->connectScreen(screen);
	_globalSettingsState->connectScreen(screen);
	_sceneEditState->connectScreen(screen);
	_sceneSettingsState->connectScreen(screen);
	_sequenceEditState->connectScreen(screen);
	_sequencePianoRollState->connectScreen(screen);
	_sequenceSelectState->connectScreen(screen);
	_sequenceSettingsState->connectScreen(screen);
}
