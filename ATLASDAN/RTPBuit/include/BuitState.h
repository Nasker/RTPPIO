#pragma once

#include "BuitDevicesManager.hpp"

class BuitState {
protected:
	BuitDevicesManager* _devices;
public:
  	virtual void singleClick() = 0;
	virtual void doubleClick() = 0;
	virtual void longClick() = 0;
	virtual void rotaryTurned(ControlCommand command) = 0;
	virtual void threeAxisChanged(ControlCommand command) = 0;
	virtual void trellisPressed(ControlCommand command) = 0;
	virtual void trellisReleased(ControlCommand command) = 0;

	void connectDevices(const BuitDevicesManager& outDevices) {
		_devices = (BuitDevicesManager*) &outDevices;
	}
};
