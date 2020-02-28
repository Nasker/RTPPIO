/*
	RTPTapTempo.cpp - Class for implementing a Promediated Tap Tempo
  Created by Oscar Martínez Carmona @ RockinTechProjects, September 29, 2014.
*/


#include "Arduino.h"
#include "RTPTapTempo.h"


RTPTapTempo::RTPTapTempo(int initTempo){
  Tempo = initTempo;
	pastMillis = millis();
  medianCounter = 0;
}


void RTPTapTempo::read(){ 
	  int period = millis() - pastMillis;
     pastMillis = millis();
     if((period < 2000) && (period > 200)){
       tempoMedian[medianCounter] = 60.0 / (float(period)/1000.0);
       int tempoMedianCalc=0;
       for(int i=0; i<=medianCounter; i++){
         tempoMedianCalc += tempoMedian[i];  
       }
       Tempo = tempoMedianCalc / (float(medianCounter) + 1);
       medianCounter++;
       if(medianCounter >= 4){
        // Serial.print("->TEMPO: ");
         //Serial.print(Tempo);
         //Serial.println(" bpm");
         //medianCounter=0;
       }
     }
     else{ 
       medianCounter=0;   
       //Serial.print("Too short or too long! :");
       //Serial.println(period);
     }
 }

 float RTPTapTempo::getTempo(){
  return Tempo;
 }





