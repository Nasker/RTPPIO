/*
	RTPUltraSonic.h - Class for reading and managing an HR-SC04 Ultrasonic Ranging Module.
	Based uppon J.Rodrigo ( http://www.jra.so ) work on Ultrasonic library!
	Created by Oscar Martínez Carmona @ RockinTechProjects, August 19, 2014.
*/

#ifndef RTPUltraSonic_h
#define RTPUltraSonic_h

#include "Arduino.h"

class RTPUltraSonic{
	int _trigPin;
	int _echoPin;
	long _timeOut;
	long _duration, _distance, _maxDistance;
	
	public:
		RTPUltraSonic(int trigPin, int echoPin);
		RTPUltraSonic(int trigPin, int echoPin, long timeOut);
		long timing();
		long ranging();
		bool inRange();
};

#endif