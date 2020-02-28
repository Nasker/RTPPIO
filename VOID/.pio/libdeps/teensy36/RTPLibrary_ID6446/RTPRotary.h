/*
	RTPRotary.h - Class for reading and managing a Rotary Encoder.
	Created by Oscar Martínez Carmona @ RockinTechProjects, September 18 2018.
*/

#ifndef RTPRotary_h
#define RTPRotary_h

#include "Arduino.h"
#include <Encoder.h>

class RTPRotary: public Encoder{
    long _oldPosition  = -999;
    int _ID;
  public:
    RTPRotary(int ID, int leftRotPin, int rightRotPin):Encoder(leftRotPin,rightRotPin){
    	_ID = ID;
    };
    void callbackOnRotation( void (*userFunc)(int,String,int,int) );
  };

#endif