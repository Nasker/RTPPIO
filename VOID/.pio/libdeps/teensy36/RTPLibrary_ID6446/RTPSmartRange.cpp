/*
	RTPSmartRange.cpp - Class for reading and managing a PushButton.
	Created by Oscar Martínez Carmona @ RockinTechProjects, February 4, 2014.
	Al .cpp només hi implementem els mètodes declarats al .h
*/

#include "Arduino.h"
#include "RTPSmartRange.h"


RTPSmartRange::RTPSmartRange(byte numberZones, byte numberStepsInZone){
	_id = 0;
	_numberZones = numberZones;
	_numberStepsInZone = numberStepsInZone;
	_rangeMaxim = ANAL_MAX;
	_rangeMinim = 0;
} 

RTPSmartRange::RTPSmartRange(byte numberZones, byte numberStepsInZone, float rangeMaxim){
	_id = 0;
	_numberZones = numberZones;
	_numberStepsInZone = numberStepsInZone;
	_rangeMaxim = rangeMaxim;
	_rangeMinim = 0;
} 

RTPSmartRange::RTPSmartRange(int id, byte numberZones, byte numberStepsInZone, float rangeMinim, float rangeMaxim){
	_id = id;
	_numberZones = numberZones;
	_numberStepsInZone = numberStepsInZone;
	_rangeMaxim = rangeMaxim;
	_rangeMinim = rangeMinim;
} 


void RTPSmartRange::setNumberZones(byte numberStepsInZone){
	_numberStepsInZone = numberStepsInZone;
}  

void RTPSmartRange::setNumberStepsInZone(byte steps){
	_numberStepsInZone = steps;
}

void RTPSmartRange::setBoundaries(int rangeMinim, int rangeMaxim){
	_rangeMaxim = rangeMaxim;
	_rangeMinim = rangeMinim;
}

float RTPSmartRange::calculateNormalisedRead(int actualRead){
	_normalizedRead = float(actualRead - _rangeMinim) / float(_rangeMaxim - _rangeMinim);
	if(_normalizedRead > 1.0) _normalizedRead = 1.0;
	if(_normalizedRead < 0.0) _normalizedRead = 0.0;
	return _normalizedRead;
}

byte RTPSmartRange::getCurrentZone(int inputRange){
	calculateNormalisedRead(inputRange);
	//Serial.println(inputRange);
	_currentZone = floor(_normalizedRead * float(_numberZones));
	return _currentZone;
}

byte RTPSmartRange::getCurrentStepInZone(int inputRange){
	inputRange = constrain(inputRange,0,_rangeMaxim);
	calculateNormalisedRead(inputRange);
	_currentZone = floor(_normalizedRead * float(_numberZones));
	_currentStep = ceil(_normalizedRead * (_numberZones * _numberStepsInZone));
	_currentStepInZone = _currentStep - ( _numberStepsInZone * _currentZone);
	return _currentStepInZone;
}

byte RTPSmartRange::getCurrentStep(int inputRange){
	calculateNormalisedRead(inputRange);
	_currentZone = floor(_normalizedRead * float(_numberZones));
	_currentStep = ceil(_normalizedRead * (_numberZones * _numberStepsInZone))-1;
	return _currentStep;
} 

void RTPSmartRange::stepChanged(void (*f)(int, String,int,int)){
	if(_currentStep != _pastStep){
		(*f) (_id, "CHANGED", _currentStep, _currentZone);
	} 
	_pastStep = _currentStep;
}  

int RTPSmartRange::rectFretBoardRead(int fretBoardRead){
	int rectOutput=0;
  	if(fretBoardRead < 15) rectOutput = 0;
  	else if( (fretBoardRead >= 15) && (fretBoardRead < 31) ) rectOutput = 1; 
  	else if( (fretBoardRead >= 31) && (fretBoardRead < 73) ) rectOutput = 2; 
  	else if( (fretBoardRead >= 73) && (fretBoardRead < 110) ) rectOutput = 3; 
  	else if( (fretBoardRead >= 110) && (fretBoardRead < 144) ) rectOutput = 4; 
 	else if( (fretBoardRead >= 144) && (fretBoardRead < 170) ) rectOutput = 5; 
 	else if( (fretBoardRead >= 170) && (fretBoardRead < 200) ) rectOutput = 6; 
  	else if( (fretBoardRead >= 200) && (fretBoardRead < 230) ) rectOutput = 7; 
 	else if( (fretBoardRead >= 230) && (fretBoardRead < 250) ) rectOutput = 8; 
 	else if( (fretBoardRead >= 250) && (fretBoardRead < 280) ) rectOutput = 9;
 	else if( (fretBoardRead >= 280) && (fretBoardRead < 300) ) rectOutput = 10; 
 	else if( (fretBoardRead >= 300) && (fretBoardRead < 336) ) rectOutput = 11; 
 	else if( (fretBoardRead >= 336) && (fretBoardRead < 370) ) rectOutput = 12; 
 	else if( (fretBoardRead >= 370) && (fretBoardRead < 398) ) rectOutput = 13; 
 	else if( (fretBoardRead >= 398) && (fretBoardRead < 428) ) rectOutput = 14; 
 	else if( (fretBoardRead >= 428) && (fretBoardRead < 466) ) rectOutput = 15; 
 	else if( (fretBoardRead >= 466) && (fretBoardRead < 504) ) rectOutput = 16; 
 	else if( (fretBoardRead >= 504) && (fretBoardRead < 546) ) rectOutput = 17;
  	else if( (fretBoardRead >= 546) && (fretBoardRead < 588) ) rectOutput = 18; 
  	else if( (fretBoardRead >= 588) && (fretBoardRead < 643) ) rectOutput = 19; 
 	else if( (fretBoardRead >= 643) && (fretBoardRead < 688) ) rectOutput = 20; 
  	else if( (fretBoardRead >= 688) && (fretBoardRead < 755) ) rectOutput = 21; 
  	else if( (fretBoardRead >= 755) && (fretBoardRead < 823) ) rectOutput = 22; 
 	else if( (fretBoardRead >= 823) && (fretBoardRead < 904) ) rectOutput = 23; 
 	else if(fretBoardRead >= 904) rectOutput = 24;   

 	if(rectOutput > 12) rectOutput=12;
  	return rectOutput;
}