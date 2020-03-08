
#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <RTPMusicController.h>
#include <RTPSmartRange.h>
#include <RTPMidi2Freq.h>
#include <RTPButton.h>

#include "constants.h"

#include "Flute_100kbyte_samples.h"
#include "DXBass3_samples.h"
#include "SESub3_samples.h"

#define KNOB_RANGE 0
#define RESO_IN_PIN 3

byte rootNoteNumber = 0; //C=0,D=2;E=4;F=5;G=7;A=9;B=11; (sostinguts +1..)

byte scaleNumber = 8;  //1-Ionian/2-Dorian/3-Phrygian/4-Lydian/5-Mixolydian
//6-Aeolian/7-Locrian/8-Harmonic Minor/9-Spanish Gipsy
//10-Hawaian/11-Blues/12-Japanese

AudioSynthWavetable      wavetable;
AudioOutputI2S           i2s1;
AudioFilterStateVariable filter;
AudioConnection          patchCord1(wavetable, 0, filter, 0);
AudioConnection          patchCord3(filter, 0, i2s1, 0);
AudioConnection          patchCord4(filter, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

RTPMusicController       mControl;

RTPSmartRange knobsRange[4]{
  RTPSmartRange(MORPH_RANGE, 1, 1023, 0, 1023),
  RTPSmartRange(RESO_RANGE, 4, 12, 0, 1023),
  RTPSmartRange(CUTOFF_RANGE, 1, 1023, 0, 1023),
  RTPSmartRange(BEND_RANGE, 1, 1023, 0, 1023)
};

RTPMidi2Freq             midi2freq;
RTPButton         button(1, 1, PULLUP);

float freq;

void setup() { 
  Serial.begin(115200);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  filter.resonance(3.0);

  mControl.setCurrentRootNote(rootNoteNumber);
  mControl.setCurrentScale(scaleNumber);
  //mControl.setCurrentOctave(5);
  knobsRange[1].setNumberStepsInZone(mControl.scales.getSteps());
  wavetable.setInstrument(Flute_100kbyte);
  wavetable.amplitude(1);
}


void actOnKnobRangeChange(int ID, String callbackString, uint16_t step, int zone){
  switch(ID){
    case RESO_RANGE:{
      Serial.printf("%d CHANGED step:%d  zone:%d\n", ID, step, zone);
      mControl.setCurrentOctave(zone);
      mControl.setCurrentStep(step);
      freq = midi2freq.getFreq(mControl.getCurrentMidiNote());
      wavetable.setFrequency(freq);
      break;
    }
    case MORPH_RANGE:{
      break;
    }
    case BEND_RANGE:{
      break;
    }
    case CUTOFF_RANGE:{
      Serial.printf("%d CHANGED step:%d  zone:%d\n", ID, step, zone);
      float cutoff = 16000 * pow(step/ 1023.0, 4);
      if (cutoff >= 16000) 
        cutoff = 16000;
      filter.frequency(cutoff);
      break;
    }
  }
}

void actOnButtonCallback(int ID, String callbackString){
  Serial.println(callbackString);
  if(callbackString == "CLICK"){
    wavetable.playFrequency(freq);
  }
  if(callbackString == "DECLICK"){
    wavetable.stop();
  }
}

void loop() {
  button.callback(actOnButtonCallback);
  for(int i=0; i<N_KNOBS; i++){
    knobsRange[i].getCurrentStepInZone(analogRead(knobsInputs[i]));
    knobsRange[i].stepChanged(actOnKnobRangeChange);
  }
}