/*
	RTPTriggerMessage.cpp - Class for managing an digitalInput associated with a fileplayer
	Created by Oscar Martínez Carmona @ RockinTechProjects, March 20, 2017.
*/


#include "Arduino.h"
#include "RTPTriggerMessage.h"


RTPTriggerMessage::RTPTriggerMessage(byte inputPin, byte outputPin, String fileName, int mode){
  _inputPin = inputPin;
  _outputPin = outputPin;
  _coundGuardCycles = 500;
  _countGuard = 0;
  _prevState = digitalRead(_inputPin);
  _mode = mode;
  _fileName = fileName;
  if(mode == NORMAL){
  	pinMode(_inputPin,INPUT);
  }
  if(mode == PULLUP){
  	pinMode(_inputPin,INPUT_PULLUP);
  }
  pinMode(_outputPin,OUTPUT);
}


void RTPTriggerMessage::read(){
	  if(_mode) _state = !digitalRead(_inputPin);
	  else _state = digitalRead(_inputPin);
 }

void RTPTriggerMessage::write(boolean state){
 	digitalWrite(_outputPin,state);
}

void RTPTriggerMessage::setOutputHigh(){
	write(HIGH);
}	

void RTPTriggerMessage::setOutputLow(){
	write(LOW);
}

bool RTPTriggerMessage::pressed(){
    read();
    return _state;
 }

void RTPTriggerMessage::setCountGuard(int countGuardCycles){
	_coundGuardCycles = countGuardCycles;
}


void RTPTriggerMessage::callbackStateChange(void (*f)(String, RTPTriggerMessage*)){
  if(_shootGuard) _countGuard++;

  if(_countGuard >= _coundGuardCycles){
      _shootGuard=false;
      _countGuard=0;
  }

  read();
  if(_state != _prevState){
    if(_state && !_shootGuard){
      (*f)("RISING", this);
      _shootGuard=true;
      _countGuard=0;
    }
    if(!_state){
      (*f)("FALLING", this);
    }
  }
  _prevState=_state;
}

String RTPTriggerMessage::getFileName(){
	return _fileName;
}