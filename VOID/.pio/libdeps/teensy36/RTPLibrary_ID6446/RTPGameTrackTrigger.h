/*
	RTPGameTrackTrigger.h - Class for turning a GameTrack z axis into a MIDI Trigger (aimmed on DrumKits)
	Created by Oscar Martínez Carmona @ RockinTechProjects, May 27, 2018.
*/

#ifndef RTPGameTrackTrigger_h
#define RTPGameTrackTrigger_h

#include "Arduino.h"

class RTPGameTrackTrigger{
	int _zAxisInput;
	int _midiChannel;
	int _midiNumber;
	int _zAxisRead;
	bool _state;
	bool _prevState;
	int _velocity;
	bool _fixedVelocity;
	int _threshold;
	int _envMax;
	int _envMin;
	bool _shootGuard;
    int _coundGuardCycles;  
    int _countGuard;  
    int _zAxisPastRead;
	
	
	public:
		RTPGameTrackTrigger(int zAxisInput, int midiChannel, int midiNumber);
		void callibrate(int threshold);
		void setTreshold(int threshold);
		void setFixedVelocity(bool fixedVelocity);
		void setCountGuard(int countGuardCycles);
		void readnShoot(void (*f)(String,int,int,int));

	private:
		void midiSend();

};

#endif