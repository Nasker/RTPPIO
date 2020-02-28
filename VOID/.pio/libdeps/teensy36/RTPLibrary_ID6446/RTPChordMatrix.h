/*
	RTPChordMatrix.h - Class to create and manage a matrix of Chords
	Created by Oscar Martínez Carmona @ RockinTechProjects, May 10, 2014.
*/

#ifndef RTPChordMatrix_h
#define RTPChordMatrix_h   

#include "Arduino.h" 

   const byte chordStep[8][6]={
      {0,12}, //Octave
      {0,7},   //Fifth
      {0,4,7,12},  //Major
      {0,3,7,12},  //Minor
      {0,4,7,10},  //Major 7th
      {0,3,7,10},  //Minor 7th
      {0,4,10,15},  //Hendrixian
      {0,6,10,16,21,26} //Mystic
    };

class RTPChordMatrix{

  byte _chordType;
  byte _stepChord;
  byte _nSteps;

	public:                      
	RTPChordMatrix();         
    void setChordType(byte chordType);
    byte getChordStep(byte step);
    byte getChordSteps();
    byte getChordType();
};

#endif