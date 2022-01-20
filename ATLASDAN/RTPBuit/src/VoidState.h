#pragma once

#include "BuitOutDevicesManager.hpp"

class VoidState {
protected:
	BuitOutDevicesManager* _outDevices;
public:
  	virtual void singleClick() = 0;
	virtual void doubleClick() = 0;
	virtual void tripleClick() = 0;
	virtual void longClick() = 0;

	void connectOutDevices(const BuitOutDevicesManager& outDevices) {
		_outDevices = (BuitOutDevicesManager*) &outDevices;
	}
};
