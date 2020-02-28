/*
  RTPRotaryClick.cpp - Class for reading and managing a Rotary Encoder with click button.
  Created by Oscar Martínez Carmona @ RockinTechProjects, October 6, 2017.
*/


#include "Arduino.h"
#include "RTPRotaryClick.h"

void RTPRotaryClick::callbackOnRotation( void (*userFunc)(String,int) ){
	long newPosition = read()/4;
  	if (newPosition < _oldPosition) {
   		_oldPosition = newPosition;
   		(*userFunc)("ROTATING LEFT",newPosition);
  	}
  	else if (newPosition > _oldPosition) {
   		_oldPosition = newPosition;
   		(*userFunc)("ROTATING RIGHT",newPosition);
  	}
}