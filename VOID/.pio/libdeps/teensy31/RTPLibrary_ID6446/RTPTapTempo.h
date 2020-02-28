/*
	RTPTapTempo.h - Class for implementing a Promediated Tap Tempo
	Created by Oscar Martínez Carmona @ RockinTechProjects, September 29, 2014.
*/

#ifndef RTPTapTempo_h
#define RTPTapTempo_h

#include "Arduino.h"

class RTPTapTempo{
	unsigned long pastMillis;
 	float Tempo;
 	float tempoMedian[8];
	int medianCounter;
	
	public:
		RTPTapTempo(int initTempo);
		void read();
		float getTempo();
};

#endif