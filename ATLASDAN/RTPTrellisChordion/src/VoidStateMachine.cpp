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

VoidStateMachine::VoidStateMachine(){ //, LiquidScreen& lScreen
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

void VoidStateMachine::singleClick(){
  _state->singleClick();
}

void VoidStateMachine::doubleClick(){
  _state->doubleClick();
}

void VoidStateMachine::tripleClick(){
  _state->tripleClick();
}

void VoidStateMachine::longClick(){
  _state->longClick();
}

void VoidStateMachine::setState(VoidState* state){
  _state = state;
}

VoidState* VoidStateMachine::getInitState(){
  return _initState;
}

VoidState* VoidStateMachine::getTransportState(){
  return _transportState;
}

VoidState* VoidStateMachine::getGlobalSettingsState(){
  return _globalSettingsState;
}

VoidState* VoidStateMachine::getSceneEditState(){
  return _sceneEditState;
}

VoidState* VoidStateMachine::getSceneSettingsState(){
  return _sceneSettingsState;
}

VoidState* VoidStateMachine::getSequenceEditState(){
  return _sequenceEditState;
}

VoidState* VoidStateMachine::getSequencePianoRollState(){
  return _sequencePianoRollState;
}

VoidState* VoidStateMachine::getSequenceSelectState(){
  return _sequenceSelectState;
}

VoidState* VoidStateMachine::getSequenceSettingsState(){
  return _sequenceSettingsState;
}

void VoidStateMachine::connectScreen(const RTPScreen& screen){
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
