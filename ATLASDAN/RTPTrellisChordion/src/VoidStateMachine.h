#pragma once

#include "VoidState.h"
#include "RTPScreen.hpp"

class BuitStateMachine{
	BuitState* _state;
	BuitState* _initState;
	BuitState* _transportState;
	BuitState* _globalSettingsState;
	BuitState* _sceneEditState;
	BuitState* _sceneSettingsState;
	BuitState* _sequenceEditState;
	BuitState* _sequencePianoRollState;
	BuitState* _sequenceSelectState;
	BuitState* _sequenceSettingsState;

public:
	BuitStateMachine();  //, LiquidScreen& lScreen
	void singleClick();
	void doubleClick();
	void tripleClick();
	void longClick();

	void setState(BuitState* state);

	BuitState* getInitState();

	BuitState* getTransportState();

	BuitState* getGlobalSettingsState();

	BuitState* getSceneEditState();

	BuitState* getSceneSettingsState();

	BuitState* getSequenceEditState();

	BuitState* getSequencePianoRollState();

	BuitState* getSequenceSelectState();

	BuitState* getSequenceSettingsState();

	void connectScreen(const RTPScreen& screen);
};
