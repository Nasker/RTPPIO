/*
	RTPNkButton.cpp -  Class for mannaging two LED NK PushButtons
  Created by Oscar Martínez Carmona @ RockinTechProjects, July 13, 2015.
*/

#include "Arduino.h"
#include "RTPNkButton.h"


RTPNkButton::RTPNkButton(int buttonInput){
	_buttonInput = buttonInput;
  _firstLedOutput = buttonInput + 1;
  _secondLedOutput = buttonInput + 2;
  pinMode(_buttonInput, INPUT_PULLUP);
  pinMode(_firstLedOutput, OUTPUT);
  pinMode(_secondLedOutput, OUTPUT);
  _defaultColor = YELLOW;
}

RTPNkButton::RTPNkButton(int buttonInput, int color){
  _buttonInput = buttonInput;
  _firstLedOutput = buttonInput + 1;
  _secondLedOutput = buttonInput + 2;
  pinMode(_buttonInput, INPUT_PULLUP);
  pinMode(_firstLedOutput, OUTPUT);
  pinMode(_secondLedOutput, OUTPUT);
  _defaultColor = color;
}

void RTPNkButton::setColor(int color){
  if(color == RED) setRedLight();
  if(color == GREEN) setGreenLight();
  if(color == YELLOW) setYellowLight();
  if(color == NO_COLOR) setNoLight();
}

void RTPNkButton::setDefaultColor(int color){
  _defaultColor = color;
  setColor(_defaultColor);
}

void RTPNkButton::initializeButton(int midiChannel, int midiNumber){
  _midiChannel = midiChannel;
  _midiNumber = midiNumber;
  _countGuard = 0;
  _shootGuard = false;
  _coundGuardCycles = 100;
  _velocity = 127;
  setColor(_defaultColor);
}

void RTPNkButton::setCountGuard(int countGuardCycles){
	_coundGuardCycles = countGuardCycles;
}

void RTPNkButton::buttonCallback(void (*f)(String,int,int,int)){
  if(_shootGuard) _countGuard++;

  if(_countGuard >= _coundGuardCycles){
      _shootGuard=false;
      _countGuard=0;
  }

  _state = !digitalRead(_buttonInput);  
  
  if(_state != _prevState){
    if((_state)&&(!_shootGuard)){
      (*f)("PRESSED",_midiChannel,_midiNumber,_velocity);
      setColor(NO_COLOR);
      _shootGuard=true;
      _countGuard=0;
    }
    if(!_state){
      (*f)("RELEASED",_midiChannel,_midiNumber,_velocity);
      setColor(_defaultColor);
    }
    _prevState = _state;
  }
}

void RTPNkButton::setRedLight(){
  digitalWrite(_firstLedOutput, LOW);
  digitalWrite(_secondLedOutput, HIGH);
}

void RTPNkButton::setYellowLight(){
  digitalWrite(_firstLedOutput, HIGH);
  digitalWrite(_secondLedOutput, HIGH);
}

void RTPNkButton::setGreenLight(){
  digitalWrite(_firstLedOutput, HIGH);
  digitalWrite(_secondLedOutput, LOW);
}

void RTPNkButton::setNoLight(){
  digitalWrite(_firstLedOutput, LOW);
  digitalWrite(_secondLedOutput, LOW);
}