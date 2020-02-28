/*
	RTPPickup.h - Class or reading and managing a PickUp.
	Created by Oscar Martínez Carmona @ RockinTechProjects, May 25, 2014.
*/

#ifndef RTPPickup_h
#define RTPPickup_h 

#include "Arduino.h" 
#define ANAL_MAX 1023.0

class RTPPickup{       
	int _input;  
	int _currentValue;  
    bool _state;  
    int _treshold;    	
    void read();   

	public:                      
	RTPPickup(int input);     
    bool sounding();   
    float getCurrentValue();    
    void setTreshold(int treshold);   
};

#endif