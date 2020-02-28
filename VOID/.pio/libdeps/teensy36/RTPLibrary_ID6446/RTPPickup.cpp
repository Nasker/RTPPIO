/*
	RTPPickup.cpp - Class or reading and managing a PickUp.
	Created by Oscar Martínez Carmona @ RockinTechProjects, May 25, 2014.
*/


#include "Arduino.h"
#include "RTPPickup.h"


RTPPickup::RTPPickup(int input){ 		
  _input = input;
  read();
  setTreshold(10);
}


void RTPPickup::read(){
	_currentValue = analogRead(_input);
	if(_currentValue > _treshold) _state=true;
	else _state = false;
}

void RTPPickup::setTreshold(int treshold){
  _treshold = treshold;
}

bool RTPPickup::sounding(){
	read();
  return _state;
}

float RTPPickup::getCurrentValue(){
  read();
  return _currentValue/ANAL_MAX;
}
