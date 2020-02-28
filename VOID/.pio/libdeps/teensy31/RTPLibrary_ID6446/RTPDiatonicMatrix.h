/*
	RTPDiatonicMatrix.h - RTPDiatonicMatrix, Declaració de la classe que conté la matriu d'escales 
	diatòniques.
	Created by Oscar Martínez Carmona & Oriol Corroto @ RockinTechProjects, April 9, 2014.
*/

#ifndef RTPDiatonicMatrix_h
#define RTPDiatonicMatrix_h   

#include "Arduino.h" 
  const byte toneStep[13][13] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, //0-Chromatic
    {0, 2, 4, 5, 7, 9, 11, 12}, //1-Ionian
    {0, 2, 3, 5, 7, 9, 10, 12}, //2-Dorian
    {0, 1, 3, 5, 7, 8, 10, 12}, //3-Phrygian
    {0, 2, 4, 6, 7, 9, 11, 12}, //4-Phrygian
    {0, 2, 4, 5, 7, 9, 10, 12}, //5-Mixolydian
    {0, 2, 3, 5, 7, 8, 10, 12}, //6-Aeolian
    {0, 1, 3, 5, 6, 8, 10, 12}, //7-Locrian
    {0, 2, 3, 5, 7, 8, 11, 12}, //8-Harmonic Minor
    {0, 1, 4, 5, 7, 8, 10, 12}, //9-Spanish Gipsy
    {0, 2, 3, 5, 7, 9, 11, 12}, //10-Hawaian
    {0, 3, 5, 6, 7, 10, 12}, //11-Blues
    {0, 1, 5, 7, 8, 12} //12-Japanese   
  };

class RTPDiatonicMatrix{

// Array de coeficients de semitons equivalents a cada escala.
  byte _tonality;
  byte _stepScale;
  byte _nSteps;
  byte _step;
  byte _numberScales;

	public:                        //A public hi declarem els mètodes que volem emprar desde fora de la classe!
		RTPDiatonicMatrix();         //Mètode constructor(imprescindible per inicialitzar la classe!
    void setTonality(byte tonality);
    byte getTonality();
    byte getSteps();
    byte getScaleStep(byte stepScale);
    byte getNumberScales();
    
  private:

};

#endif