/*
	RTPPitchControl.h -
	
	Created by Oscar Martínez Carmona & Oriol Corroto @ RockinTechProjects, April 9, 2014.
*/

#ifndef RTPPitchControl_h
#define RTPPitchControl_h   

#include "Arduino.h" 

class RTPPitchControl{

int _pitchBendRange;
int _bendReadCenter;
float _bendRead;
float _bendReadMapped;
float _pitchBendOut;

	public:                        
		RTPPitchControl();         
		float getPitchBend(float bendRead);
		void setPitchRange(byte rangeSemitones);
};

#endif