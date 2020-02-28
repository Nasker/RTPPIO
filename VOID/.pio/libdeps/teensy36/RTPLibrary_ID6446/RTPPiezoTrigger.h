/*
	RTPPiezoTrigger.h - Class for turning a PiezoBuzzer into a MIDI Trigger (aimmed on DrumKits)
	Created by Oscar Martínez Carmona @ RockinTechProjects, January 23, 2014.
*/

#ifndef RTPPiezoTrigger_h
#define RTPPiezoTrigger_h

#include "Arduino.h"

class RTPPiezoTrigger{
	int _piezoInput;
	int _midiChannel;
	int _midiNumber;
	int _piezoRead;
	bool _state;
	bool _prevState;
	int _velocity;
	bool _fixedVelocity;
	int _treshold;
	int _envMax;
	int _envMin;
	bool _shootGuard;
    int _coundGuardCycles;  
    int _countGuard;  
	
	
	public:
		RTPPiezoTrigger(int piezoInput, int midiChannel, int midiNumber);
		void callibrate(int treshold);
		void setTreshold(int treshold);
		void setFixedVelocity(bool fixedVelocity);
		void setCountGuard(int countGuardCycles);
		void readnShoot(void (*f)(String,int,int,int));

	private:
		void midiSend();

};

#endif