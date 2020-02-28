/*
	RTPTouchTrigger.h - Class for turning a TouchRead into a MIDI Trigger (aimed on DrumKits)
	Created by Oscar Martínez Carmona @ RockinTechProjects, June 1, 2018.
*/

#ifndef RTPTouchTrigger_h
#define RTPTouchTrigger_h

#include "Arduino.h"

class RTPTouchTrigger{
	int _piezoInput;
	int _midiChannel;
	int _midiNumber;
	
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
    String _type;
	
	
	public:
		int _piezoRead;
		RTPTouchTrigger(int piezoInput, int midiChannel, int midiNumber);
		RTPTouchTrigger(int piezoInput, int midiChannel, int midiNumber, String type);
		void callibrate(int treshold);
		void setTreshold(int treshold);
		void setFixedVelocity(bool fixedVelocity);
		void setCountGuard(int countGuardCycles);
		void readnShoot(void (*f)(String,int,int,int));
		void setBoundaries(int envMin, int envMax, int treshold);
		int getEnvMin();
		int getEnvMax();
		int getTreshold();

	private:
		void midiSend();

};

#endif