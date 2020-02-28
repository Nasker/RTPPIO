/*
	RTPPeriodicBang.h - Class that gives a callback at a periodic rate.
	Created by Oscar Martínez Carmona @ RockinTechProjects, June 21, 2014.
*/

#ifndef RTPPeriodicBang_h
#define RTPPeriodicBang_h

#include "Arduino.h"

class RTPPeriodicBang{
	unsigned int _figurePeriod;
	unsigned long _millisPast;
	int _iddleCounter;
	int _iddleCounterCurrent;
	
	public:
		RTPPeriodicBang(unsigned figurePeriod);
		RTPPeriodicBang(unsigned int figurePeriod, int iddleCounter);
		void setFigurePeriod(unsigned int figurePeriod);
		int getFigurePeriod();
		void callbackPeriodBang( void (*f)(String) );
		void callbackIddleCounter( void (*f)(String, int) );
		void resetIddleCounter();
};

#endif