#include <Arduino.h>
byte rootNoteNumber = 0; //C=0,D=2;E=4;F=5;G=7;A=9;B=11; (sostinguts +1..)

byte scaleNumber = 8;  //1-Ionian/2-Dorian/3-Phrygian/4-Lydian/5-Mixolydian
//6-Aeolian/7-Locrian/8-Harmonic Minor/9-Spanish Gipsy
//10-Hawaian/11-Blues/12-Japanese

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "mixingArrays.h"
#include "constants.h"

#include <RTPMusicController.h>
#include <RTPSmartRange.h>
#include <RTPMidi2Freq.h>
#include <RTPButton.h>
#include <RTPPitchControl.h>
#include <RTPLedArray.h>
#include <RTPDeltaMix.h>

AudioInputI2S            i2s1;
AudioSynthWaveform       waveform1;
AudioSynthWaveform       waveform2;
AudioSynthWaveform       waveform3;
AudioSynthWaveform       waveform4;
AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioFilterStateVariable filter1;
AudioEffectMultiply      multiply1;
AudioFilterStateVariable filter2;
AudioEffectAbs           absObj;
AudioOutputI2S           i2s2;
AudioOutputUSB           usbOut;
AudioAnalyzePeak         rms1;

AudioConnection          patchCord0(i2s1, 0, absObj, 0);
AudioConnection          patchCord1(waveform3, 0, mixer1, 2);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord3(waveform4, 0, mixer1, 3);
AudioConnection          patchCord4(waveform1, 0, mixer1, 0);
AudioConnection          patchCord5(absObj, 0, filter1, 0);
AudioConnection          patchCord6(mixer1, 0, multiply1, 0);
AudioConnection          patchCord7(filter1, 0, multiply1, 1);
AudioConnection          patchCord8(filter1, 0, filter2, 1);
AudioConnection          patchCord9(multiply1, 0, filter2, 0);
AudioConnection          patchCord10(filter2, 0, mixer2, 0);
AudioConnection          patchCord11(mixer2, 0, i2s2, 0);
AudioConnection          patchCord12(mixer2, 0, i2s2, 1);
AudioConnection          patchCord13(mixer2, 0, usbOut, 0);
AudioConnection          patchCord14(mixer2, 0, usbOut, 1);
AudioConnection          patchCord15(mixer2, 0, rms1, 0);

AudioControlSGTL5000     sgtl5000_1;

RTPMusicController       mControl;
RTPSmartRange            fretBoardRange(FRETBOARD_RANGE, 4, 12, 0, 1023/2);

RTPSmartRange knobsRange[4]{
  RTPSmartRange(CUTOFF_RANGE, 1, 1023, 0, 1023),
  RTPSmartRange(RESO_RANGE, 1, 1023, 0, 1023),
  RTPSmartRange(MORPH_RANGE, 1, 1023, 0, 1023),
  RTPSmartRange(BEND_RANGE, 1, 1023, 0, 1023)
};

RTPSmartRange            scalesRange(1, 24);
RTPSmartRange            rootNoteRange(2, 12);

RTPButton                switchTonality(ROOT_SW_PIN, PULLUP);
RTPButton                switchScale(SCALE_SW_PIN, PULLUP);
RTPButton                downOctaveSwitch(OCT_DWN_PIN, PULLUP);
RTPButton                upOctaveSwitch(OCT_UP_PIN, PULLUP);

RTPPitchControl          pitchBend;
RTPLedArray              leds(5, 4);
RTPMidi2Freq             midi2freq;
RTPDeltaMix              deltaMix;

const byte ledArray[] = {0, 3, 1, 2};
int fretBoardRead;

void scaleChange(int ID, String callbackString) {
  Serial.println(callbackString);
  if (callbackString == "DECLICK") {
    mControl.scales.setTonality(scalesRange.rectFretBoardRead(fretBoardRead));
    fretBoardRange.setNumberStepsInZone(mControl.scales.getSteps());
  }
}

void tonalityChange(int ID, String callbackString) {
  Serial.println(callbackString);
  if (callbackString == "DECLICK") {
    int currentRootNote = rootNoteRange.rectFretBoardRead(fretBoardRead);
    if (currentRootNote < 1) currentRootNote = 1;
    else if (currentRootNote > 12) currentRootNote = 12;
    currentRootNote--;
    mControl.setCurrentRootNote(currentRootNote);
  }
}

void octaveDown(int ID, String callbackString) {
  Serial.println(callbackString);
  if (callbackString == "CLICK") {
    mControl.downOctave();
    leds.update(ledArray[mControl.getOctaveOffset()]);
  }
}

void octaveUp(int ID, String callbackString) {
  Serial.println(callbackString);
  if (callbackString == "CLICK") {
    if (mControl.getOctaveOffset() < 3) {
      mControl.upOctave();
      leds.update(ledArray[mControl.getOctaveOffset()]);
    }
  }
}

void actOnKnobRangeChange(int ID, String callbackString, int step, int zone){
  Serial.printf("%d CHANGED value: %d\n", ID, step);
  switch(ID){
    case FRETBOARD_RANGE:{
      mControl.setCurrentOctave(zone);
      mControl.setCurrentStep(step);
      float freq = midi2freq.getFreq(mControl.getCurrentMidiNote());
      freq *= pitchBend.getPitchBend(1023 - analogRead(BEND_IN_PIN));
      waveform1.frequency(freq/2);
      waveform2.frequency(freq/2);
      waveform3.frequency(freq/2);
      waveform4.frequency(freq/2);
      break;
    }
    case RESO_RANGE:{
      filter2.resonance(map(step, 0, 1023, 3, 7));
      filter2.octaveControl(map(step, 0, 1023, 0, 5));
      break;
    }
    case MORPH_RANGE:{
      waveform2.amplitude( arrayJ[analogRead(MORPH_IN_PIN)] );
      waveform3.amplitude( arrayK[analogRead(MORPH_IN_PIN)] );
      waveform4.amplitude( arrayL[analogRead(MORPH_IN_PIN)] );
      break;
    }
    case BEND_RANGE:{
      break;
    }
    case CUTOFF_RANGE:{
      float cutoff = 16000 * pow(step/ 1023.0, 4)  + midi2freq.getFreq(mControl.getCurrentMidiNote()) / 2.0;
      if (cutoff >= 16000) 
        cutoff = 16000;
      filter2.frequency(cutoff);
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start setup!");
  AudioMemory(12);
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(10);
  sgtl5000_1.lineOutLevel(17);
  sgtl5000_1.volume(0.6);

  filter1.frequency(1.0);

  filter2.frequency(200.0);
  filter2.resonance(0.0);
  filter2.octaveControl(5.0);

  waveform1.begin(0.0, 55.0, WAVEFORM_SINE);
  waveform2.begin(1.0, 55.0, WAVEFORM_PULSE);
  waveform3.begin(1.0, 55.0, WAVEFORM_SAWTOOTH);
  waveform4.begin(1.0, 55.0, WAVEFORM_SQUARE);

  for (int i = 0; i < 4; i++) 
    mixer1.gain(i, 0.25);

  mixer2.gain(0, 3.0);

  mControl.setCurrentRootNote(rootNoteNumber);
  mControl.setCurrentScale(scaleNumber);
  fretBoardRange.setNumberStepsInZone(mControl.scales.getSteps());

  leds.update(ledArray[mControl.getOctaveOffset()]);

  Serial.println("Finish Setup!");
}


void loop() {
  switchScale.callback(scaleChange);
  switchTonality.callback(tonalityChange);
  upOctaveSwitch.callback(octaveUp);
  downOctaveSwitch.callback(octaveDown);

  fretBoardRange.getCurrentStep(analogRead(FRETBOARD_IN_PIN));
  fretBoardRange.stepChanged(actOnKnobRangeChange);

  for(int i=0; i<N_KNOBS; i++){
    knobsRange[i].getCurrentStep(analogRead(knobsInputs[i]));
    knobsRange[i].stepChanged(actOnKnobRangeChange);
  }
}
  //fretBoardRead = analogRead(FRETBOARD_IN_PIN) * 2;

  //mControl.setCurrentOctave(fretBoardRange.getCurrentZone(fretBoardRead));
  //mControl.setCurrentStep(fretBoardRange.getCurrentStepInZone(fretBoardRead));
/*
  float freq = midi2freq.getFreq(mControl.getCurrentMidiNote());
  freq *= pitchBend.getPitchBend(1023 - analogRead(BEND_IN_PIN));

  waveform1.frequency(freq/2);
  waveform2.frequency(freq/2);
  waveform3.frequency(freq/2);
  waveform4.frequency(freq/2);*/
/*
  waveform2.amplitude( arrayJ[analogRead(MORPH_IN_PIN)] );
  waveform3.amplitude( arrayK[analogRead(MORPH_IN_PIN)] );
  waveform4.amplitude( arrayL[analogRead(MORPH_IN_PIN)] );*/

  /*int smoothRead = analogRead(CUTOFF_IN_PIN);
  float cutoff = 16000 * pow(smoothRead / 1023.0, 4)  + freq / 2;
  if (cutoff >= 16000) cutoff = 16000;
  filter2.frequency(cutoff);*/
  /*filter2.resonance(map(analogRead(RESO_IN_PIN), 0, 1023, 3, 7));
  filter2.octaveControl(map(analogRead(RESO_IN_PIN), 0, 1023, 0, 5));*/
//}