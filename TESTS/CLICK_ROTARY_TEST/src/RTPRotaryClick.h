/*
	RTPRotaryClick.h - Class for reading and managing a Rotary QuadEncoder with click button.
	Updated by Oscar Martínez Carmona @ RockinTechProjects, January 17, 2022.
*/

#pragma once

#include "Arduino.h"
#include "Encoder.h"
#include "RTPClickButton.h"
#include "RTPStructs.hpp"

class RTPRotaryClick: public Encoder, public RTPClickButton{
  protected:
    long int _oldPosition  = -999;
  public:
    RTPRotaryClick();
    RTPRotaryClick(int leftRotPin, int rightRotPin, int buttonPin, boolean active, boolean pullup):Encoder(leftRotPin,rightRotPin),RTPClickButton(buttonPin,active,pullup){};
    void callbackOnRotation( void (*userFunc)(ControlCommand) );
  };