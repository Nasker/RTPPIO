/*
	RTPSoftPot.h - Class or reading and managing a SoftPot
	Created by Oscar Martínez Carmona @ RockinTechProjects, March 24, 2014.
*/

#ifndef RTPSoftPot_h
#define RTPSoftPot_h 

#include "Arduino.h" 

class RTPSoftPot{       
  protected:
	  int _input;  
	  int _currentValue;        
    bool _state;          
    bool _prevState;  
    bool _shootGuard;
    int _coundGuardCycles;  
    int _countGuard;  
	
    void read();   

	public:                      
		RTPSoftPot(int input);     
    bool pressed();   
    int getCurrentValue();       
    void callbackPress ( void (*f)(String) );
	
             
};

#endif