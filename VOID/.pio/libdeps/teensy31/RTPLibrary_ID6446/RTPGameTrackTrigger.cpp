/*
	RTPGameTrackTrigger.cpp - Class for turning a GameTrack z axis into a MIDI Trigger (aimmed on DrumKits)
  Created by Oscar Martínez Carmona @ RockinTechProjects, May 27, 2018.
*/


#include "Arduino.h"
#include "RTPGameTrackTrigger.h"


RTPGameTrackTrigger::RTPGameTrackTrigger(int zAxisInput, int midiChannel, int midiNumber){
	_zAxisInput = zAxisInput;
	_midiChannel = midiChannel;
	_midiNumber = midiNumber;
  _countGuard=0;
  _shootGuard=false;
  _coundGuardCycles=2000;
  _fixedVelocity = true;
  _zAxisPastRead = 0;
}

void RTPGameTrackTrigger::callibrate(int threshold){
  digitalWrite(12,HIGH);
 _envMax=0;
  _envMin=1023;
 while (millis() < 4000) {
    int sensorValue = analogRead(_zAxisInput);

    if (sensorValue > _envMax) {
      _envMax = sensorValue;
    }

    if (sensorValue < _envMin) {
      _envMin = sensorValue;
    }

 }
 digitalWrite(12,LOW);
  //_treshold = _envMax/4;
  _threshold = threshold;
}

void RTPGameTrackTrigger::setTreshold(int threshold){
	_threshold = threshold;
}

void RTPGameTrackTrigger::setFixedVelocity(bool fixedVelocity){
	_fixedVelocity = fixedVelocity;
}

void RTPGameTrackTrigger::setCountGuard(int countGuardCycles){
	_coundGuardCycles = countGuardCycles;
}

void RTPGameTrackTrigger::readnShoot(void (*f)(String,int,int,int)){
  _zAxisRead = analogRead(_zAxisInput);
  Serial.println(_zAxisRead);

  if(_shootGuard) _countGuard++;

  if(_countGuard >= _coundGuardCycles){
      _shootGuard=false;
      _countGuard=0;
  }
 /*
  if(_zAxisRead < _treshold){
      _state = true;  
    }
    else{
      _state = false;
   }
  */
  //if(_state != _prevState){
   if((_zAxisRead < _threshold)&& (_zAxisPastRead > _threshold)){
    if(!_shootGuard){
    	if(!_fixedVelocity){
    		_velocity = 127/ ((100 - _threshold) / (_zAxisRead - _threshold));
      		if(_velocity>127) _velocity=127;
    	}
      else _velocity = 100;
      //midiSend();
      (*f)("ON",_midiChannel,_midiNumber,_velocity);
      _shootGuard=true;
      _countGuard=0;
      //delay(10);
    }
    if(!_state){
      _velocity=0;
      //midiSend();
      (*f)("OFF",_midiChannel,_midiNumber,_velocity);
    }
    _prevState = _state;
  }
  _zAxisPastRead = _zAxisRead;
}

void RTPGameTrackTrigger::midiSend(){
  Serial.write(_midiChannel);
  Serial.write(_midiNumber);
  Serial.write(_velocity);
}