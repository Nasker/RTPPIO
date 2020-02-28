/*
	RTPMusicController.cpp - Controlador Musical per als projectes de RTP.
	Created by Oscar Martínez Carmona @ RockinTechProjects, May 8, 2014.
*/


#include "Arduino.h"
#include "RTPMusicController.h"


RTPMusicController::RTPMusicController(){ 		//Constructor
	_CNote = 36;
	_currentNote = _CNote;
	_lastNote = _currentNote;
	_currentRootNote = _CNote;
	_currentOctave = 0;
	_octaveOffset = 0;
	_currentScale = 0;
	_currentChord = 0;
	_lastChord = _currentChord;
	_voices = 1;
	_numberOctaves = 2;
	_velocity = 100;
	_midiChannel = 0x90;

}


void RTPMusicController::setCurrentNote(byte currentNote){
	_currentNote = currentNote;
}   

void RTPMusicController::setCurrentStep(byte currentStep){
	_currentStep = currentStep;
}

void RTPMusicController::setLastNote(byte lastNote){
	_lastNote = lastNote;
} 
void RTPMusicController::setCurrentRootNote(byte currentRootNote){
	_currentRootNote = _CNote + currentRootNote;
}
void RTPMusicController::setCurrentOctave(byte currentOctave){
	_currentOctave = currentOctave;
}
void RTPMusicController::upOctave(){
	if(_octaveOffset < 5 ){
		_octaveOffset++;
	} 
}
void RTPMusicController::downOctave(){
	if(_octaveOffset > 0 ){
		_octaveOffset--;
	} 
}
void RTPMusicController::setCurrentScale(byte currentScale){
	_currentScale = currentScale;
	scales.setTonality(_currentScale);
}
void RTPMusicController::setCurrentChord(byte currentChord){
	_currentChord = currentChord;
}
void RTPMusicController::setLastChord(byte lastChord){
	_lastChord = lastChord;
} 
void RTPMusicController::setVoices(byte voices){
	_voices = voices;
}
void RTPMusicController::setVelocity(byte velocity){
	_velocity = velocity;
}
void RTPMusicController::setNumberOctaves(byte numberOctaves){
	_numberOctaves = numberOctaves;
}
void RTPMusicController::setMidiChannel(byte midiChannel){
	_midiChannel = midiChannel;
}       

byte RTPMusicController::getCurrentMidiNote(){
	return _currentRootNote + scales.getScaleStep(_currentStep) + _currentOctave * 12 + _octaveOffset * 12; 
}


byte RTPMusicController::getCurrentNote(){
	return _currentNote;
}   
byte RTPMusicController::getLastNote(){
	return _lastNote;
} 

byte RTPMusicController::getCurrentRootNote(){
	return _currentRootNote- _CNote;
}
byte RTPMusicController::getCurrentScale(){
	return _currentScale;
}
byte RTPMusicController::getCurrentChord(){
	return _currentChord;
}
byte RTPMusicController::getLastChord(){
	return _lastChord;
} 
byte RTPMusicController::getVoices(){
	return _voices;
}
byte RTPMusicController::getVelocity(){
	return _velocity;
}
byte RTPMusicController::getNumberOctaves(){
	return _numberOctaves;
}   
byte RTPMusicController::getCurrentOctave(){
	return _currentOctave;
}   

byte RTPMusicController::getOctaveOffset(){
	return _octaveOffset;
} 

byte RTPMusicController::getMidiChannel(){
	return _midiChannel;
} 

String RTPMusicController::getCurrentRootNoteName(){
	byte rootIndex = _currentRootNote - _CNote;
	return rootName[rootIndex];
	//return rootIndex;
}  

String RTPMusicController::getScaleName(){
	return scaleName[_currentScale];
	//return rootIndex;
} 





