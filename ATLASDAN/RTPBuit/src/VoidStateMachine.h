#pragma once

#include "VoidState.h"
#include "BuitOutDevicesManager.hpp"

class VoidStateMachine{
	VoidState* _state;
	VoidState* _initState;
	VoidState* _transportState;
	VoidState* _globalSettingsState;
	VoidState* _sceneEditState;
	VoidState* _sceneSettingsState;
	VoidState* _sequenceEditState;
	VoidState* _sequencePianoRollState;
	VoidState* _sequenceSelectState;
	VoidState* _sequenceSettingsState;

public:
	VoidStateMachine();  //, LiquidScreen& lScreen
	void singleClick();
	void doubleClick();
	void tripleClick();
	void longClick();

	void setState(VoidState* state);

	VoidState* getInitState();

	VoidState* getTransportState();

	VoidState* getGlobalSettingsState();

	VoidState* getSceneEditState();

	VoidState* getSceneSettingsState();

	VoidState* getSequenceEditState();

	VoidState* getSequencePianoRollState();

	VoidState* getSequenceSelectState();

	VoidState* getSequenceSettingsState();

	void connectOutDevices(const BuitOutDevicesManager& outDevices);
};
