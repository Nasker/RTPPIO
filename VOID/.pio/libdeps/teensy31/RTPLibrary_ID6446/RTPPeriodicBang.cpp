/*
	RTPPeriodicBang.cpp - Class that gives a callback at a periodic rate.
	Created by Oscar Martínez Carmona @ RockinTechProjects, June 21, 2014.
*/


#include "Arduino.h"
#include "RTPPeriodicBang.h"


  RTPPeriodicBang::RTPPeriodicBang(unsigned int figurePeriod){
    _figurePeriod = figurePeriod;
    _millisPast = millis();
    _iddleCounter = 0;
  }

  RTPPeriodicBang::RTPPeriodicBang(unsigned int figurePeriod, int iddleCounter){
    _figurePeriod = figurePeriod;
    _millisPast = millis();
    _iddleCounter = iddleCounter;
    _iddleCounterCurrent = _iddleCounter;
  }

  void RTPPeriodicBang::setFigurePeriod(unsigned int figurePeriod){
    _figurePeriod = figurePeriod;
  }

 int RTPPeriodicBang::getFigurePeriod(){
    return _figurePeriod;
  }

  void RTPPeriodicBang::callbackPeriodBang( void (*f)(String) ){
    if( millis() >= (_millisPast + _figurePeriod) ){
      (*f)("BANG");
      _millisPast=millis();
    }
}

  void RTPPeriodicBang::callbackIddleCounter( void (*f)(String,int) ){
    if( millis() >= (_millisPast + _figurePeriod) ){
      _iddleCounterCurrent--;
      _millisPast=millis();
      (*f)("TICK",_iddleCounterCurrent);
    }
    if(_iddleCounterCurrent < 1) (*f)("IDDLE EXPIRED",_iddleCounterCurrent);
}
	void RTPPeriodicBang::resetIddleCounter(){
		_iddleCounterCurrent = _iddleCounter;
	}
