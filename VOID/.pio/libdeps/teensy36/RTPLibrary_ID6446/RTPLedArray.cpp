/*
	RTPLedArray.cpp - Class for managing an array of LEDS
	Created by Oscar Martínez Carmona @ RockinTechProjects, June 10, 2014.
*/


#include "Arduino.h"
#include "RTPLedArray.h"


RTPLedArray::RTPLedArray(byte firstPin, byte nLeds){ 
  _firstPin = firstPin;
  _nLeds = nLeds;
  for(byte i = _firstPin ; i < _firstPin+_nLeds; i++){
    pinMode(i,OUTPUT);
  }
  } 
/*
RTPLedArray::RTPLedArray(byte ledArray[], byte nLeds){
	_nLeds = nLeds;
	for(byte i=0; i<nLeds; i++){
		_ledArray[i] = ledArray[i];
		pinMode(_ledArray[i], OUTPUT);
	}
}
*/
void RTPLedArray::update(byte value){
for(byte i = _firstPin ; i < _firstPin+_nLeds; i++){
    if(value + _firstPin == i) digitalWrite(i,true);
    else digitalWrite(i,false);
  }  
}
/*
void RTPLedArray::updateArray(byte value){
for(byte i = 0 ; i < _nLeds; i++){
    if(value == i) digitalWrite(i,true);
    else digitalWrite(i,false);
  }  
}*/