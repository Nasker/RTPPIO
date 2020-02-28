/*
  RTPBatteryControl.cpp - Class for controlling the battery level
  Created by Oscar Martínez Carmona @ RockinTechProjects, October 2, 2018.
*/

#include "Arduino.h"
#include "RTPBatteryControl.h"
#include <RTPSmooth.h>


RTPBatteryControl::RTPBatteryControl(int batteryLevelInputPin, int adcLevels){
	_batteryLevelInputPin = batteryLevelInputPin;
  _batteryLowLevelThreshold = 3.3;
  _powerSupplyThreshold = 4.0;
  _adcLevels = adcLevels;
}

void RTPBatteryControl::setBatteryLowLevelThreshold(float batteryLowLevelThreshold){
	_batteryLowLevelThreshold = batteryLowLevelThreshold;
}

void RTPBatteryControl::setPowerSupplyThreshold(float powerSupplyThreshold){
  _powerSupplyThreshold = powerSupplyThreshold;
}

void RTPBatteryControl::monitorBatteryCallbacks(void (*f)(String,float)){
  _vccRead = calcVoltageLevel();
  if(_vccRead > _powerSupplyThreshold) _vccExternalSource = true;  
  else _vccExternalSource = false;
  
  if(_vccExternalSource != _prevLevelState){
    if(_vccExternalSource){
      (*f)("EXTERNAL POWER",_vccRead);
    }
    if(!_vccExternalSource){
      (*f)("BATTERY POWER", _vccRead);
    }
    _prevLevelState = _vccExternalSource;
  }
  if(_vccRead < _batteryLowLevelThreshold) _lowBattery = true;  
  else _lowBattery = false;
  
  if(_lowBattery != _prevBatteryState){
    if(_lowBattery){
      (*f)("LOW_BATTERY!",_vccRead);
    }
    _prevBatteryState = _lowBattery;
  }
}

float RTPBatteryControl::calcVoltageLevel(){
  int average = adcAverage.smooth(analogRead(_batteryLevelInputPin));
  return  ( average * (3.3 / float(_adcLevels) )) * 2;
}

float RTPBatteryControl::getVoltageLevel(){
  return calcVoltageLevel();
}

float RTPBatteryControl::getVoltageLevelFast(){
  return  ( analogRead(_batteryLevelInputPin) * (3.3 / float(_adcLevels) )) * 2;
}

float RTPBatteryControl::getHueLevel(){
  float volts = getVoltageLevelFast();
  float voltageHue = constrain(map(round( volts * 100), 300, 370, 0, 120), 0, 120);
  Serial.print("Measured volts are: ");
  Serial.print(volts);
  Serial.print("\t Battery hue is: ");
  Serial.println(voltageHue);
  return voltageHue;
}