#pragma once

#include "RTPScreen.hpp"

class BuitState {
protected:
	RTPScreen* _screen;
public:
  	virtual void singleClick() = 0;
	virtual void doubleClick() = 0;
	virtual void tripleClick() = 0;
	virtual void longClick() = 0;

	void connectScreen(const RTPScreen& screen) {
		_screen = (RTPScreen*) &screen;
	}
};
