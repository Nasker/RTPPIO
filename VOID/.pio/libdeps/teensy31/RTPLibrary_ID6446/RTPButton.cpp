/*
	RTPButton.cpp - Class for reading and managing a PushButton.
	Created by Oscar Martínez Carmona @ RockinTechProjects, February 4, 2014.
*/


#include "Arduino.h"
#include "RTPButton.h"


RTPButton::RTPButton(byte buttonInput, int mode){
  _buttonInput = buttonInput;
  _coundGuardCycles = 500;;
  _countGuard = 0;
  _holdCounter = 0;
  _prevState = digitalRead(_buttonInput);
  _mode = mode;
  if(mode == NORMAL){
  	pinMode(buttonInput,INPUT);
  }
  if(mode == PULLUP){
  	pinMode(buttonInput,INPUT_PULLUP);
  }
}

RTPButton::RTPButton(byte ID, byte buttonInput, int mode){
  _ID = ID;				
  _buttonInput = buttonInput;
  _coundGuardCycles = 500;;
  _countGuard = 0;
  _holdCounter = 0;
  _prevState = digitalRead(_buttonInput);
  _mode = mode;
  if(mode == NORMAL){
  	pinMode(buttonInput,INPUT);
  }
  if(mode == PULLUP){
  	pinMode(buttonInput,INPUT_PULLUP);
  }
}


void RTPButton::read(){
	  if(_mode) _state = !digitalRead(_buttonInput);
	  else _state = digitalRead(_buttonInput);
 }

bool  RTPButton::pressed(){
    read();
    return _state;
 }

void RTPButton::setCountGuard(int countGuardCycles){
	_coundGuardCycles = countGuardCycles;
}

void RTPButton::callbackClick(void (*f)(String)){
  read();
  if(_state != _prevState){
    if(_state){
      //Serial.println("CLICK");
      (*f)("CLICK");
    }
  }
  _prevState=_state;
}

void RTPButton::callbackDeClick(void (*f)(String)){
  read();
  if(_state != _prevState){
    if(!_state){
      //Serial.println("CLICK");
      (*f)("DECLICK");
    }
  }
  _prevState=_state;
}

void RTPButton::callback(void (*f)(int,String)){
  if(_shootGuard) _countGuard++;

  if(_countGuard >= _coundGuardCycles){
      _shootGuard=false;
      _countGuard=0;
  }

  read();
  if(_state != _prevState){
    if(_state && !_shootGuard){
      //Serial.println("CLICK");
      (*f)(_ID,"CLICK");
      _shootGuard=true;
      _countGuard=0;
    }
    if(!_state){
      //Serial.println("CLICK");
      (*f)(_ID,"DECLICK");
    }
  }
  _prevState=_state;
}

void RTPButton::callbackHold( void (*f) (String) ){
	read();
	if(_state){
		_holdCounter++;
      	if(_state && _holdCounter>1000){
        	(*f)("HOLD");
        	_holdCounter = 0;	
      	}
	}
    if(!_state) _holdCounter=0;
}


