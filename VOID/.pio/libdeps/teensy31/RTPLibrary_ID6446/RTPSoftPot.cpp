/*
	RTPSoftPot.cpp - Class or reading and managing a SoftPot
	Created by Oscar Martínez Carmona @ RockinTechProjects, March 24, 2014.
*/


#include "Arduino.h"
#include "RTPSoftPot.h"


RTPSoftPot::RTPSoftPot(int input){ 		
  _input = input;
  read();
  _prevState = false;
  _countGuard=0;
  _shootGuard=false;
  _coundGuardCycles=50;
}


void RTPSoftPot::read(){
	_currentValue = analogRead(_input);
	if(_currentValue > 10) _state=true;
	else _state = false;
}

bool RTPSoftPot::pressed(){
	read();
  return _state;
}

int  RTPSoftPot::getCurrentValue(){
  read();
  return _currentValue;
}

void RTPSoftPot::callbackPress(void (*f)(String)){
  read();

  if(_shootGuard) _countGuard++;

  if(_countGuard >= _coundGuardCycles){
      _shootGuard=false;
      _countGuard=0;
  }

  if(_state != _prevState){
    if((_state)&&(!_shootGuard)){
      //Serial.println("PRESSED");
      (*f)("PRESSED");
      _shootGuard=true;
      _countGuard=0;
      //delay(20);
    }

    if(!_state){
      //Serial.println("DEPRESSED");
      (*f)("DEPRESSED");
      //delay(20);
    }
  }
  _prevState=_state;
}
