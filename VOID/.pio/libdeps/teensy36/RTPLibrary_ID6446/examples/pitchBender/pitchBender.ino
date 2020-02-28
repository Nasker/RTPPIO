/*	melodyCricket-ino - Version 2.0 of melodyCricket using the library RTPPitchControl.h
	Created by Oscar Martínez Carmona & Oriol Corroto @ RockinTechProjects, April 14, 2014.
*/

#include <NewTone.h>
#include <RTPPitchControl.h>

const int inputFader = 0;
const int ledOut = 11;
const int speakerOut = 7;
const int pushIn = 8;

int reference = 440;
RTPPitchControl instancia1;

void setup() {                
    Serial.begin(9600);
    pinMode(ledOut,OUTPUT);
    pinMode(speakerOut,OUTPUT);
    pinMode(pushIn,INPUT);
}


void loop() {
        float fader = analogRead(inputFader);
        int pwm = (fader/1023.0)*255;
        
        float pitch= instancia1.getPitchBend(fader);
        float noteFreq = reference*pitch;
        
        analogWrite(ledOut,pwm);
        boolean button = digitalRead(pushIn);
        
        if(button) NewTone(speakerOut,noteFreq);
        else noNewTone(speakerOut);

        
}
