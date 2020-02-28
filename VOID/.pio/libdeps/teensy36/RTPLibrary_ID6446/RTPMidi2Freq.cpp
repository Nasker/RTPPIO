/*
  RTPMidi2Freq.h - RTPMidi2Freq, Class that contains and array of equivalence between midi notes and frequencies.
  Oscar Martínez Carmona @ RTP December 27 2014.
*/


#include "Arduino.h"
#include "RTPMidi2Freq.h"


RTPMidi2Freq::RTPMidi2Freq(){
}

float RTPMidi2Freq::getFreq(byte midiNumber){
    return midi2Freq[midiNumber];
}