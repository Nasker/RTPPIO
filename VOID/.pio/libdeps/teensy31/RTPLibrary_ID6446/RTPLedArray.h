/*
	RTPLedArray.h - Class for managing an array of LEDS
	Created by Oscar Martínez Carmona @ RockinTechProjects, June 10, 2014.
*/

#ifndef RTPLedArray_h
#define RTPLedArray_h

#include "Arduino.h"

class RTPLedArray{
	byte _firstPin;
	byte _nLeds;
	byte _ledArray[];
	
	public:
		RTPLedArray(byte firstPin, byte nLeds);
		//RTPLedArray(byte ledArray[], byte nLeds);

		void update(byte value);
		//void updateArray(byte value);
};

#endif