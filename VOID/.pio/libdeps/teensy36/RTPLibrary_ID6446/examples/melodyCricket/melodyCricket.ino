/*	melodyCricket-ino - Version 2.0 of melodyCricket using the library RTPDiatonicMatrix
	Created by Oscar Martínez Carmona & Oriol Corroto @ RockinTechProjects, April 9, 2014.
*/


#include <NewTone.h>
#include <RTPDiatonicMatrix.h>

const int inputFader = 0;  //entrada valor de fader
const int ledOut = 11;     //entrada valor de led
const int speakerOut = 7;  //entrada de sortida de so
const int pushIn = 8;      //valor de entrada de boto d'activació
const int pushScale = 6;   //valor d'entrada de boto de canvi de escala

//Type of Scales
//0-Chromatic//1-Ionian//2-Dorian//3-Phrygian//4-Lydian
//5-Mixolydian//6-Aeolian//7-Locrian//8-Harmonic Minor
//9-Spanish Gipsy//10-Hawaian//11-Blues//12-Japanese   

int scale =0;
RTPDiatonicMatrix instancia1;

void setup() {                
    Serial.begin(9600);
    pinMode(ledOut,OUTPUT);
    pinMode(speakerOut,OUTPUT);
    pinMode(pushIn,INPUT);
    pinMode(pushScale,INPUT);
}


void loop() {
        instancia1.setTonality(scale);
        boolean Escala = digitalRead(pushScale);
        if (Escala){
        delay(1000); scale++;
        }
        if (scale>12) scale=0;
        int fader = analogRead(inputFader);
        int pwm = (fader/1023.0)*255;
        float faderNorm = (fader/1023.0); 
        
        int dStep = map(fader,0,1023,0,instancia1.getSteps());
        float coef=pow(2,float (instancia1.getCoef(dStep)/12.));
        float noteFreq = 440 * coef;
        
        analogWrite(ledOut,pwm);
        boolean button = digitalRead(pushIn);
        
        if(button) NewTone(speakerOut,noteFreq);
        else noNewTone(speakerOut);
}
