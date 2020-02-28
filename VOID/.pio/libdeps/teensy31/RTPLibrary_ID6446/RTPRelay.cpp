/*
	RTPRelay.cpp - Class for controlling a Relay
	Created by Oscar Martínez Carmona @ RockinTechProjects, October 14, 2018.
*/


#include "Arduino.h"
#include "RTPRelay.h"


RTPRelay::RTPRelay(byte relayOutputPin){
  _relayOutputPin = relayOutputPin;
  _state = false;
  pinMode(_relayOutputPin, OUTPUT);
  _isInvertedLogic = false;
  write();
  
}

RTPRelay::RTPRelay(byte relayOutputPin, bool isInvertedLogic){
  _relayOutputPin = relayOutputPin;
  _state = false;
  pinMode(_relayOutputPin, OUTPUT);
  _isInvertedLogic = isInvertedLogic;
  write();
}

bool RTPRelay::getState(){
	return _state;
}

void RTPRelay::setState(bool state){
	_state = state;
	write();
}

void RTPRelay::switchState(){
	_state = !_state;
	write();
}


void RTPRelay::write(){
	if(_isInvertedLogic) digitalWrite(_relayOutputPin, !_state);
	else digitalWrite(_relayOutputPin, _state);
}