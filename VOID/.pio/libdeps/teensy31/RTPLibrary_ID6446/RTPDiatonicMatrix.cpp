
/*	RTPDiatonicMatrix-cpp - Class to return the coef. from the diatonic matrix
	Created by Oscar Martínez Carmona & Oriol Corroto @ RockinTechProjects, April 9, 2014.

	Al .cpp només hi implementem els mètodes declarats al .h
*/


#include "Arduino.h"
#include "RTPDiatonicMatrix.h"


RTPDiatonicMatrix::RTPDiatonicMatrix(){
    _tonality = 0;
    _stepScale = 0;
    _nSteps = 0;
    _step = 0;
    _numberScales = 13;
}

void RTPDiatonicMatrix::setTonality(byte tonality){
    _tonality = tonality;
}

byte RTPDiatonicMatrix::getTonality(){
    return _tonality;
}

byte RTPDiatonicMatrix::getSteps(){
if (_tonality == 0) _nSteps=12;                                        //fraccions de notes en funció de la escala
    else if (_tonality < 10 && _tonality > 0)  _nSteps = 7;
    else if (_tonality == 10) _nSteps = 6;
    else _nSteps = 5;  
    return _nSteps;
}

byte RTPDiatonicMatrix::getScaleStep(byte stepScale){
_stepScale = stepScale;
_step= toneStep[_tonality][_stepScale];
return _step;
}

byte RTPDiatonicMatrix::getNumberScales(){
    return _numberScales;
}