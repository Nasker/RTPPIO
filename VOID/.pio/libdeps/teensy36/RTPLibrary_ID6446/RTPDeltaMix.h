/*
	RTPDeltaMix.h - Classe per transformar una variable en tres(seh!).
	Created by Oscar Martínez Carmona @ RockinTechProjects, May 25, 2014.
*/

#ifndef RTPDeltaMix_h
#define RTPDeltaMix_h   

#include "Arduino.h" 
#define ANAL_MAX 1023.0

class RTPDeltaMix{     

	float _normalizedRead;
	float _gain1;
    float _gain2;
    float _gain3;

	public:                
		RTPDeltaMix(); 
        void calculate(int inputRead);  
        float getFirst();
        float getSecond();
        float getThird();
};

#endif