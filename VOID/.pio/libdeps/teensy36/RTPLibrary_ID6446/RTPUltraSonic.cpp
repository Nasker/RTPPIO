/*
  RTPUltraSonic.h - Class for reading and managing an HR-SC04 Ultrasonic Ranging Module.
  Based uppon J.Rodrigo ( http://www.jra.so ) work on Ultrasonic library!
  Created by Oscar Martínez Carmona @ RockinTechProjects, August 19, 2014.
*/


#include "Arduino.h"
#include "RTPUltraSonic.h"


RTPUltraSonic::RTPUltraSonic(int trigPin, int echoPin){
  _trigPin = trigPin;
  _echoPin = echoPin;
  pinMode(_trigPin,OUTPUT);
  pinMode(_echoPin,INPUT);
  _timeOut=3000; // fixed time out [us] -> maximum distance range 50cms
  _maxDistance = _timeOut /29/2;
}

RTPUltraSonic::RTPUltraSonic(int trigPin, int echoPin, long timeOut){
  _trigPin = trigPin;
  _echoPin = echoPin;
  pinMode(_trigPin,OUTPUT);
  pinMode(_echoPin,INPUT);
  _timeOut = timeOut;
  _maxDistance = _timeOut/29/2;
}

long RTPUltraSonic::timing(){
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin,LOW);
  _duration = pulseIn(_echoPin, HIGH, _timeOut);
  if(!_duration) _duration = _timeOut;
  return _duration;
}

long RTPUltraSonic::ranging(){
  timing();
  _distance = _duration/29/2;
  return _distance;
}

bool RTPUltraSonic::inRange(){
  //ranging();
  return _distance < _maxDistance;
}