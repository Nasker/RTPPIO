/*
	RTPDeltaMix.cpp - Classe per transformar una variable en tres(seh!).
	Created by Oscar Martínez Carmona @ RockinTechProjects, May 25, 2014.
*/

#include "Arduino.h"
#include "RTPDeltaMix.h"

RTPDeltaMix::RTPDeltaMix(){
} 
void RTPDeltaMix::calculate(int inputRead){
	_normalizedRead = float(inputRead)/ANAL_MAX;
    float linearTau = _normalizedRead*TWO_PI;
	_gain1=abs((cos(linearTau-(TWO_PI/6)))/2);
	_gain2=abs((cos(linearTau-(3*TWO_PI/6)))/2);
	_gain3=abs((cos(linearTau-(5*TWO_PI/6)))/2);
}

float RTPDeltaMix::getFirst(){
	return _gain1;
}

float RTPDeltaMix::getSecond(){
	return _gain2;
}
float RTPDeltaMix::getThird(){
	return _gain3;
}