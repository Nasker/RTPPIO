/*
	RTPTriggerMessage.h - Class for managing an digitalInput associated with a fileplayer
	Created by Oscar Martínez Carmona @ RockinTechProjects, March 20, 2017.
*/

#ifndef RTPTriggerMessage_h
#define RTPTriggerMessage_h

#include "Arduino.h"

#define NORMAL 0
#define PULLUP 1

class RTPTriggerMessage{
	byte _inputPin;
	byte _outputPin;
	bool _state;
	bool _prevState;
	int _coundGuardCycles;  
	int _countGuard;
	boolean _shootGuard;
	unsigned int _holdCounter;
	int _mode;
	String _fileName;
	
	public:
		RTPTriggerMessage(byte inputPin, byte outputPin, String fileName, int mode);
		bool pressed();
		void setOutputHigh();
		void setOutputLow();
		void callbackStateChange( void (*f)(String, RTPTriggerMessage*));
		void setCountGuard(int countGuardCycles);
		String getFileName();


	private:
		void read();
		void write(boolean state);
};

#endif