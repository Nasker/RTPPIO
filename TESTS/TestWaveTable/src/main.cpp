
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

#include "Flute_100kbyte_samples.h"
#include "DXBass3_samples.h"

#define KNOB_RANGE 0
#define RESO_IN_PIN 3

byte rootNoteNumber = 0; //C=0,D=2;E=4;F=5;G=7;A=9;B=11; (sostinguts +1..)

byte scaleNumber = 8;  //1-Ionian/2-Dorian/3-Phrygian/4-Lydian/5-Mixolydian
//6-Aeolian/7-Locrian/8-Harmonic Minor/9-Spanish Gipsy
//10-Hawaian/11-Blues/12-Japanese

AudioSynthWavetable      wavetable;
AudioOutputI2S           i2s1;
AudioMixer4              mixer;
AudioConnection          patchCord1(wavetable, 0, mixer, 0);
AudioConnection          patchCord2(mixer, 0, i2s1, 0);
AudioConnection          patchCord3(mixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

// Bounce objects to read pushbuttons 
Bounce button1 = Bounce(1, 50);  // 15 ms debounce time

RTPMusicController       mControl;
RTPSmartRange            knobRange(KNOB_RANGE, 4, 8, 0, 1023);
RTPMidi2Freq             midi2freq;
RTPButton         button(1, 1, PULLUP);

float freq;

void setup() { 
  Serial.begin(115200);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  mixer.gain(0, 0.7);

  mControl.setCurrentRootNote(rootNoteNumber);
  mControl.setCurrentScale(scaleNumber);
  knobRange.setNumberStepsInZone(mControl.scales.getSteps());
  
  wavetable.setInstrument(DXBass3);
  wavetable.amplitude(1);
}


void actOnKnobRangeChange(int ID, String callbackString, uint16_t step, int zone){
  Serial.printf("%d CHANGED step:%d  zone:%d\n", ID, step, zone);
  switch(ID){
    case KNOB_RANGE:{
      mControl.setCurrentOctave(zone);
      mControl.setCurrentStep(step);
      freq = midi2freq.getFreq(mControl.getCurrentMidiNote());
      wavetable.setFrequency(freq);
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
  knobRange.getCurrentStepInZone(analogRead(RESO_IN_PIN));
  knobRange.stepChanged(actOnKnobRangeChange);
}