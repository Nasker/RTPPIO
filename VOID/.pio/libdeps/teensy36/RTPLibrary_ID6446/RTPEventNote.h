/*
    RTPEventNote.h - RTPEventNote, Simple state/note/velocity object
	Created by Oscar Martínez Carmona @ RockinTechProjects, October 30, 2015.
*/

#ifndef RTPEventNote_h
#define RTPEventNote_h   
#include "Arduino.h" 

class RTPEventNote{
    boolean _state;
    byte    _note;
    int	    _read;
    byte 	_velocity;

	public:
    RTPEventNote(boolean state, byte note);
    RTPEventNote(boolean state, byte note, byte velocity);
    boolean eventState();
    byte getEventNote();
    int getEventRead();
    byte getEventVelocity();
    void setEventState(boolean state);
    void setEventNote(byte note);
    void setEventRead(int read);
    void setEventVelocity(byte velocity);
    void switchState();
};

#endif