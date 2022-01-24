#pragma once

#include "BuitOutDevicesManager.hpp"
#include "RTPSequencer.h"

class BuitState {
protected:
	BuitOutDevicesManager* _outDevices;
	RTPSequencer* _sequencer;
public:
  	virtual void singleClick() = 0;
	virtual void doubleClick() = 0;
	virtual void longClick() = 0;
	virtual void rotaryTurned(ControlCommand command) = 0;
	virtual void threeAxisChanged(ControlCommand command) = 0;
	virtual void trellisPressed(ControlCommand command) = 0;
	virtual void trellisReleased(ControlCommand command) = 0;

	void connectOutDevices(const BuitOutDevicesManager& outDevices) {
		_outDevices = (BuitOutDevicesManager*) &outDevices;
	}

	void connectSequencer(const RTPSequencer& sequencer) {
		_sequencer = (RTPSequencer*) &sequencer;
	}
};
