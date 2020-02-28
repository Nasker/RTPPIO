/*
	RTPNkButton.h - Class for mannaging two LED NK PushButtons
	Created by Oscar Martínez Carmona @ RockinTechProjects, July 13, 2015.
*/

#ifndef RTPNkButton_h
#define RTPNkButton_h

#define NO_COLOR 0
#define GREEN 1
#define YELLOW 2
#define RED 3


#include "Arduino.h"

class RTPNkButton{
	int _buttonInput;
	int _firstLedOutput;
	int _secondLedOutput;
	int _midiChannel;
	int _midiNumber;
	bool _state;
	bool _prevState;
	int _velocity;
	bool _shootGuard;
    int _coundGuardCycles;  
    int _countGuard;
    int _defaultColor;

	public:
		RTPNkButton(int buttonInput);
		RTPNkButton(int buttonInput, int color);
		void initializeButton(int midiChannel, int midiNumber);
		void setCountGuard(int countGuardCycles);
		void buttonCallback(void (*f)(String,int,int,int));
		void setColor(int color);
		void setDefaultColor(int color);
	private:
		void setRedLight();
		void setYellowLight();
		void setGreenLight();
		void setNoLight();
};

#endif