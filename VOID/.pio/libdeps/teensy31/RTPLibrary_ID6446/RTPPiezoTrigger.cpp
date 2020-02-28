/*
	RTPPiezoTrigger.cpp - Library for turning a PiezoBuzzer into a MIDI Trigger (aimmed on DrumKits)
	Created by Oscar Martínez Carmona @ RockinTechProjects, January 23, 2014.
*/


#include "Arduino.h"
#include "RTPPiezoTrigger.h"


RTPPiezoTrigger::RTPPiezoTrigger(int piezoInput, int midiChannel, int midiNumber){
	_piezoInput = piezoInput;
	_midiChannel = midiChannel;
	_midiNumber = midiNumber;
  _countGuard=0;
  _shootGuard=false;
  _coundGuardCycles=2000;
  _fixedVelocity = false;
}

void RTPPiezoTrigger::callibrate(int treshold){
  digitalWrite(12,HIGH);
 _envMax=0;
  _envMin=1023;
 while (millis() < 4000) {
    int sensorValue = analogRead(_piezoInput);

    if (sensorValue > _envMax) {
      _envMax = sensorValue;
    }

    if (sensorValue < _envMin) {
      _envMin = sensorValue;
    }

 }
 //Serial.println(_envMax);
 //Serial.println(_envMin);

 digitalWrite(12,LOW);
  //_treshold = _envMax/4;
  _treshold = treshold;
}

void RTPPiezoTrigger::setTreshold(int treshold){
	_treshold = treshold;
}

void RTPPiezoTrigger::setFixedVelocity(bool fixedVelocity){
	_fixedVelocity = fixedVelocity;
}

void RTPPiezoTrigger::setCountGuard(int countGuardCycles){
	_coundGuardCycles = countGuardCycles;
}

void RTPPiezoTrigger::readnShoot(void (*f)(String,int,int,int)){
  _piezoRead = analogRead(_piezoInput);
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
  
  if(_state != _prevState){
    if((_state)&&(!_shootGuard)){
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



void RTPPiezoTrigger::midiSend(){
  Serial.write(_midiChannel);
  Serial.write(_midiNumber);
  Serial.write(_velocity);
}

/*
void PiezoTrigger::readnShoot(){
    _piezoRead = analogRead(_piezoInput);


    //if (_growing && _piezoRead < _piezoReadPast*1.1){
  if (_piezoRead < _piezoReadPast){
     // _growing = false;
      _velocity = round(map(_piezoReadPast,_envMin, _envMax, 0, 127));
      midiSend();
      delay(20);
      _velocity=0;
  midiSend();
    }
    _piezoReadPast = _piezoRead;
  }  


  if(_piezoRead > _treshold){
      _state = true;  
    }
    else{
      _state = false;
   }
  
  if(_state != _prevState){
    if (_piezoRead < _piezoReadPast){
     // _growing = false;
      _velocity = map(_piezoReadPast,_envMin, _envMax, 0, 127);
      midiSend();
      delay(20);
    }
    if(!_state){
      _velocity=0;
      midiSend();
    }
    _prevState = _state;
    _piezoReadPast = _piezoRead;
  }
  
  _velocity=0;
  midiSend();
  delay(20); 
  
 }
 */



