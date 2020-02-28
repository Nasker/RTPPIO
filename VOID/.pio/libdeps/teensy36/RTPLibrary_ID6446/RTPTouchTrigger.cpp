/*
	RTPTouchTrigger.cpp - Class for turning a TouchRead into a MIDI Trigger (aimed on DrumKits)
	Created by Oscar Martínez Carmona @ RockinTechProjects, June 1, 2018.
*/


#include "Arduino.h"
#include "RTPTouchTrigger.h"


RTPTouchTrigger::RTPTouchTrigger(int piezoInput, int midiChannel, int midiNumber){
	_piezoInput = piezoInput;
	_midiChannel = midiChannel;
	_midiNumber = midiNumber;
  	_countGuard=0;
  	_shootGuard=false;
  	_coundGuardCycles=2;
  	_fixedVelocity = true;
}


void RTPTouchTrigger::callibrate(int treshold){
	digitalWrite(13,HIGH);	
 	_envMax=0;
 	_envMin=65000;
 	long unsigned int pastMillis = millis();
 	Serial.println("Starting callibration!");
 	 	while (millis() < pastMillis + 4000) {
 		int sensorValue;
		sensorValue = touchRead(_piezoInput);
    	if (sensorValue > _envMax) {
      		_envMax = sensorValue;
    	}

    	if (sensorValue < _envMin) {
      		_envMin = sensorValue;
    	}
 }
    _treshold = _envMin + ( _envMin / 2.0 );
 	Serial.println("Ending callibration!");
 	Serial.print("Boundaries:  -max: ");
 	Serial.print(_envMin);
 	Serial.print("\t-min: ");
 	Serial.print(_envMax);
 	Serial.print("\t-Threshold: ");
 	Serial.println(_treshold);
 	digitalWrite(13,LOW);
}

void RTPTouchTrigger::setTreshold(int treshold){
	_treshold = treshold;
}

void RTPTouchTrigger::setFixedVelocity(bool fixedVelocity){
	_fixedVelocity = fixedVelocity;
}

void RTPTouchTrigger::setCountGuard(int countGuardCycles){
	_coundGuardCycles = countGuardCycles;
}

void RTPTouchTrigger::readnShoot(void (*f)(String,int,int,int)){
	_piezoRead = touchRead(_piezoInput);
    //Serial.println(_piezoRead);
  	if(_shootGuard) _countGuard++;

  	if(_countGuard >= _coundGuardCycles){
    	_shootGuard=false;
     	_countGuard=0;
  	}
 
  	if(_piezoRead > _treshold){
    	_state = true;  
    }
    else{
    	_state = false;
   	}
  
  if( (_state != _prevState)){
    if(_state && !_shootGuard){
    	if(!_fixedVelocity){
    		_velocity = 127/ ((100 - _treshold) / (_piezoRead - _treshold));
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
}

void RTPTouchTrigger::setBoundaries(int envMin, int envMax, int treshold){
	_envMin = envMin;
	_envMax = envMax;
	_treshold= treshold;
}

int RTPTouchTrigger::getEnvMin(){
	return _envMin;
}

int RTPTouchTrigger::getEnvMax(){
	return _envMax;
}

int RTPTouchTrigger::getTreshold(){
	return _treshold;
}

void RTPTouchTrigger::midiSend(){
  Serial.write(_midiChannel);
  Serial.write(_midiNumber);
  Serial.write(_velocity);
}