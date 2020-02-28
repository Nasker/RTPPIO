
/*	RTPPitchControl-cpp - 
	Created by Oscar Martínez Carmona & Oriol Corroto @ RockinTechProjects, April 9, 2014.
*/


#include "Arduino.h"
#include "RTPPitchControl.h"

RTPPitchControl::RTPPitchControl(){
	_pitchBendRange = 12;
	_bendReadCenter = 0; 
    _bendRead = 0.0;
    _bendReadMapped = 0.0;
    _pitchBendOut = 0.0;

}

float RTPPitchControl::getPitchBend(float bendRead){
	_bendRead = bendRead;
	if(_bendRead<20) _bendReadMapped=-1;
    else if((_bendRead>=40)&&(_bendRead<=460)) _bendReadMapped = (1-(_bendRead-40)/420)*-1;
    else if((_bendRead>460)&&(_bendRead<580)) _bendReadMapped=0;
    else if((_bendRead>=580)&&(_bendRead<=980)) _bendReadMapped = (_bendRead-580)/400;
    else _bendReadMapped=1; 

    _pitchBendOut = pow(2,_pitchBendRange*_bendReadMapped/12);
    return _pitchBendOut;
}

void RTPPitchControl::setPitchRange(byte rangeSemitones){
	_pitchBendRange = rangeSemitones;
}