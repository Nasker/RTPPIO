#include "BuitStateMachine.h"
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

void BuitStateMachine::longClick(){
  _state->longClick();
}

void BuitStateMachine::rotaryTurned(ControlCommand command){
  _state->rotaryTurned(command);
}

void BuitStateMachine::threeAxisChanged(ControlCommand command){
  _state->threeAxisChanged(command);
}

void BuitStateMachine::trellisPressed(ControlCommand command){
  _state->trellisPressed(command);
}

void BuitStateMachine::trellisReleased(ControlCommand command){
  _state->trellisReleased(command);
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

void BuitStateMachine::connectOutDevices(const BuitOutDevicesManager& outDevices){
	_initState->connectOutDevices(outDevices);
	_transportState->connectOutDevices(outDevices);
	_globalSettingsState->connectOutDevices(outDevices);
	_sceneEditState->connectOutDevices(outDevices);
	_sceneSettingsState->connectOutDevices(outDevices);
	_sequenceEditState->connectOutDevices(outDevices);
	_sequencePianoRollState->connectOutDevices(outDevices);
	_sequenceSelectState->connectOutDevices(outDevices);
	_sequenceSettingsState->connectOutDevices(outDevices);
}

void BuitStateMachine::connectSequencer(const RTPSequencer& sequencer){
  _initState->connectSequencer(sequencer);
  _transportState->connectSequencer(sequencer);
  _globalSettingsState->connectSequencer(sequencer);
  _sceneEditState->connectSequencer(sequencer);
  _sceneSettingsState->connectSequencer(sequencer);
  _sequenceEditState->connectSequencer(sequencer);
  _sequencePianoRollState->connectSequencer(sequencer);
  _sequenceSelectState->connectSequencer(sequencer);
  _sequenceSettingsState->connectSequencer(sequencer);
}
