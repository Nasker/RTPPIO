/*
	RTPRotaryClick.h - Class for reading and managing a Rotary Encoder with click button.
	Created by Oscar Martínez Carmona @ RockinTechProjects, October 6, 2017.
*/

#ifndef RTPRotaryClick_h
#define RTPRotaryClick_h

#include "Arduino.h"
#include <Encoder.h>
#include <RTPClickButton.h>


class RTPRotaryClick: public Encoder, public RTPClickButton{
    long _oldPosition  = -999;
  public:
    RTPRotaryClick(int leftRotPin, int rightRotPin, int buttonPin, boolean active, boolean pullup):Encoder(leftRotPin,rightRotPin),RTPClickButton(buttonPin,active,pullup){};
    void callbackOnRotation( void (*userFunc)(String,int) );
  };

#endif