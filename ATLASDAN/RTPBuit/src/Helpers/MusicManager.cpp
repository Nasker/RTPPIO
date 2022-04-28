#include "MusicManager.hpp"

MusicManager::MusicManager(){}

void MusicManager::setCurrentHarmony(byte channel, byte control, byte value){
    if(channel == 1 && control>=0 && control<=15 && value<=15){ 
        mControl.setCurrentRootNote(control);
        mControl.setCurrentScale(value);
        mControl.setCurrentChord(value);
        /*Serial.print(mControl.getCurrentRootNoteName());
        Serial.print("\t");
        Serial.println(mControl.getChordName());*/
    }
}