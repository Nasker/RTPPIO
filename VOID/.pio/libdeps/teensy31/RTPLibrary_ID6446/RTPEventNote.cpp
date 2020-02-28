/*
    RTPEventNote.h - RTPEventNote, Simple state/note/velocity object
	Created by Oscar Martínez Carmona @ RockinTechProjects, October 30, 2015.
*/


#include "Arduino.h"
#include "RTPEventNote.h"

RTPEventNote::RTPEventNote(boolean state, byte note){
	_state = state;
	_note = note;
	_velocity = 100;
	_read = 0;
}

RTPEventNote::RTPEventNote(boolean state, byte note, byte velocity){
	_state = state;
	_note = note;
	_velocity = velocity;
	_read = 0;
}

boolean RTPEventNote::eventState(){
	return _state;
}

byte RTPEventNote::getEventNote(){
	return _note;
}

int RTPEventNote::getEventRead(){
	return _read;
}

byte RTPEventNote::getEventVelocity(){
	return _velocity;
}

void RTPEventNote::setEventState(boolean state){
	_state = state;
}

void RTPEventNote::setEventNote(byte note){
	_note = note;
}

void RTPEventNote::setEventRead(int read){
	_read = read;
}

void RTPEventNote::setEventVelocity(byte velocity){
	_velocity = velocity;
}

void RTPEventNote::switchState(){
	_state = !_state;
}

