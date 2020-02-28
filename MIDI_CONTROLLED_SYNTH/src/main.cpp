#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <RTPMidi2Freq.h>
#include <LinkedList.h>
#include <RTPPeriodicBang.h>


#define LEVEL     7
#define CUTOFF    74
#define RESONANCE 71
#define OCTCONTRL 93
#define ATTACK    73
#define DECAY     75
#define RELEASE   72
#define SUSTAIN   10
#define MIXGAIN   91
#define WAVEFORM1 97 
#define WAVEFORM2 96
#define WAVEFORM3 66
#define WAVEFORM4 67 
#define WAVEFORM5 64
#define WAVEFORM6 65
//#define WAVEFORM7 7
#define WAVEFORM8 10

struct midiNote {
  byte note;
  byte velocity;
  float freq;
};

LinkedList<midiNote> playedFreqs;
/*
AudioSynthWaveform       waveform1;      //xy=153.99999618530273,858.3055868148804
AudioSynthWaveform       waveform3;      //xy=157.33330917358398,938.4165797233582
AudioSynthWaveform       waveform2;      //xy=158.55553817749023,900.0832176208496
AudioSynthWaveform       waveform4;      //xy=160.66665649414062,980.9721441268921
AudioMixer4              mixer3;         //xy=301.4444079928928,914.9721236758762
AudioEffectEnvelope      envelope1;      //xy=427.2221866183811,914.9721246295505
AudioFilterStateVariable filter1;        //xy=567.6666841506958,915.0833196640015
AudioEffectMultiply      multiply1;      //xy=690.8887935214573,1019.8610067897373
AudioMixer4              mixer4;         //xy=701.999930911594,920.9720812373691
AudioEffectBitcrusher    bitcrusher1;    //xy=833.3334121704102,919.8612127304077
AudioFilterBiquad        biquad1;        //xy=929.4444122314453,772.8610916137695
AudioFilterBiquad        biquad2;        //xy=952.4444122314453,1098.8610916137695
AudioEffectChorus        chorus1;        //xy=964.2221488952637,920.9722833633423
AudioEffectDelay         delay1;         //xy=1071.4444122314453,737.8610916137695
AudioEffectDelay         delay2;         //xy=1081.4444122314453,1147.8610916137695
AudioEffectFlange        flange1;        //xy=1083.1111602783203,922.0833673477173
AudioMixer4              mixer1;         //xy=1203.4444694519043,886.8610696792603
AudioMixer4              mixer2;         //xy=1206.4444694519043,974.8610696792603
AudioOutputI2S           i2s1;           //xy=1345.7777938842773,930.8610696792603
AudioConnection          patchCord1(waveform1, 0, mixer3, 0);
AudioConnection          patchCord2(waveform3, 0, mixer3, 2);
AudioConnection          patchCord3(waveform2, 0, mixer3, 1);
AudioConnection          patchCord4(waveform4, 0, mixer3, 3);
AudioConnection          patchCord5(mixer3, envelope1);
AudioConnection          patchCord6(envelope1, 0, filter1, 0);
AudioConnection          patchCord7(envelope1, 0, filter1, 1);
AudioConnection          patchCord8(filter1, 0, mixer4, 0);
AudioConnection          patchCord9(filter1, 1, mixer4, 1);
AudioConnection          patchCord10(filter1, 2, mixer4, 2);
AudioConnection          patchCord11(multiply1, 0, mixer4, 3);
AudioConnection          patchCord12(mixer4, 0, multiply1, 0);
AudioConnection          patchCord13(mixer4, 0, multiply1, 1);
AudioConnection          patchCord14(mixer4, bitcrusher1);
AudioConnection          patchCord15(bitcrusher1, chorus1);
AudioConnection          patchCord16(biquad1, delay1);
AudioConnection          patchCord17(biquad2, delay2);
AudioConnection          patchCord18(chorus1, flange1);
AudioConnection          patchCord19(delay1, 0, mixer1, 1);
AudioConnection          patchCord20(delay2, 0, mixer2, 1);
AudioConnection          patchCord21(flange1, 0, mixer1, 0);
AudioConnection          patchCord22(flange1, 0, mixer2, 0);
AudioConnection          patchCord23(mixer1, biquad1);
AudioConnection          patchCord24(mixer1, 0, i2s1, 0);
AudioConnection          patchCord25(mixer2, biquad2);
AudioConnection          patchCord26(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1045.444465637207,1346.3055696487427
// GUItool: end automatically generated code
 */
AudioSynthWaveform       waveform1;
AudioEffectEnvelope      envelope1;
AudioFilterStateVariable filter1;
AudioFilterBiquad        biquad2;
AudioFilterBiquad        biquad1;
AudioEffectDelay         delay2;
AudioEffectDelay         delay1;
AudioMixer4              mixer2;
AudioMixer4              mixer1;
AudioOutputI2S           i2s1;
AudioOutputUSB           usb1; 
AudioOutputAnalog        dac;
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, 0, filter1, 0);
AudioConnection          patchCord3(envelope1, 0, filter1, 1);
AudioConnection          patchCord4(filter1, 0, mixer1, 0);
AudioConnection          patchCord5(filter1, 0, mixer2, 0);
AudioConnection          patchCord6(biquad2, delay2);
AudioConnection          patchCord7(biquad1, delay1);
AudioConnection          patchCord8(delay2, 0, mixer2, 1);
AudioConnection          patchCord9(delay1, 0, mixer1, 1);
AudioConnection          patchCord10(mixer2, biquad2);
AudioConnection          patchCord11(mixer2, 0, i2s1, 1);
AudioConnection          patchCord12(mixer2, 0, usb1, 1);
AudioConnection          patchCord13(mixer1, biquad1);
AudioConnection          patchCord14(mixer1, 0, i2s1, 0);
AudioConnection          patchCord15(mixer1, 0, usb1, 0);
AudioConnection          patchCord16(mixer2, 0, dac, 0);
AudioControlSGTL5000     sgtl5000_1;

RTPMidi2Freq             midi2freq;
RTPPeriodicBang          updateGlide(1);

float feedback;
float reso;
float currentFreq, pastFreq, lastFreq;
float glideFreq;
float glideTime = 0;


void glide(String callbackString) {
  if (abs(currentFreq - glideFreq) > 1.0) {
    float glideInc =  (currentFreq - pastFreq) / glideTime;
    // Serial.print("GLIDE INC IS: ");
    glideFreq += glideInc;
    //Serial.println(glideInc);
    waveform1.frequency(glideFreq);
    //Serial.print("GLIDING: ");
    //Serial.println(glideFreq);
  }
}

void OnNoteOn(byte channel, byte note, byte velocity) {
  midiNote currentNote;
  currentNote.note = note;
  currentNote.velocity = velocity;
  currentNote.freq = midi2freq.getFreq(note);
  currentFreq = currentNote.freq;
  if (playedFreqs.size()) {
    pastFreq = playedFreqs.get(playedFreqs.size() - 1).freq;
    //Serial.println("TWO CONSECUTIVE NOTES, LEGATO");
  }
  else {
    pastFreq = currentFreq;
    glideFreq = currentFreq;
    envelope1.noteOn();
    //Serial.println("JUST ONE NOTE, NO LEGATO");
  }
  //currentFreq = playedFreqs.get(playedFreqs.size() - 1).freq;
  //glideFreq = pastFreq;
  playedFreqs.add(currentNote);
  waveform1.frequency(currentNote.freq);
  waveform1.amplitude(currentNote.velocity / 127.0);

  //Serial.println(currentFreq - glideFreq);
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  midiNote currentOffNote;
  currentOffNote.note = note;
  currentOffNote.velocity = velocity;
  currentOffNote.freq = midi2freq.getFreq(note);
  int i=0;
  for (; i < playedFreqs.size(); i++) {
    if (playedFreqs.get(i).note == note) playedFreqs.remove(i);
  }
  //Serial.println("HERE's A CHANGE!??!");
  if (playedFreqs.size()) { 
    currentFreq = playedFreqs.get(playedFreqs.size() - 1).freq;
    if(lastFreq!=currentFreq) waveform1.frequency(currentFreq);
    if(i != playedFreqs.size()){
      glideFreq = currentOffNote.freq;
      pastFreq = currentOffNote.freq;
      //Serial.println("Igualo a la off");
    }
    else{
      glideFreq = currentFreq;
      pastFreq = currentFreq;
      //Serial.println("Igualo a la actual");
    }
    Serial.println("PULLING OFF NOTE, PREVIOUS ON THE LIST WILL PLAY");
  }
  else {
    envelope1.noteOff();
    glideFreq = currentFreq;
    //Serial.println("LAST NOTE OFF, CLOSING ENVELOPE");
  }
  //Serial.println(currentFreq - glideFreq);
  lastFreq=currentFreq;
}

void OnControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change, ch=");
  switch (control) {
    //case LEVEL: sgtl5000_1.volume(float(value/127.0)); break;
    case CUTOFF: filter1.frequency(16000 * pow(value / 127.0, 4)); break;
    case RESONANCE:
      reso = float(value / 127.0) * 5.0;
      if (reso < 0.7) reso = 0.7;
      filter1.resonance(reso);
      break;
    case OCTCONTRL: filter1.octaveControl((float(value / 127.0) * 7.0)); break;
    case ATTACK: envelope1.attack(int(float(value / 127.0) * 500.0)); break;
    case DECAY: envelope1.decay(int(float(value / 127.0) * 100000.0)); break;
    //case RELEASE: envelope1.release(int(float(value / 127.0) * 1000.0)); break;
    case RELEASE: glideTime =(float(value / 127.0) * 1000.0); break;
    case SUSTAIN: envelope1.sustain((float(value / 127.0) * 1.0)); break;
    case MIXGAIN:
      mixer1.gain(1, (value / 127.0) * 0.6);
      mixer2.gain(1, (value / 127.0) * 0.7);
      break;
    case WAVEFORM1: waveform1.begin(WAVEFORM_SINE); break;
    case WAVEFORM2: waveform1.begin(WAVEFORM_SAWTOOTH); break;
    case WAVEFORM3: waveform1.begin(WAVEFORM_SQUARE); break;
    case WAVEFORM4: waveform1.begin(WAVEFORM_TRIANGLE); break;
    case WAVEFORM5: waveform1.begin(WAVEFORM_PULSE); break;
    case WAVEFORM6: waveform1.begin(WAVEFORM_SAWTOOTH_REVERSE); break;
   // case WAVEFORM7: waveform1.begin(WAVEFORM_SAMPLE_HOLD); break;
      //case WAVFORM8: waveform1.begin(WAVEFORM_ARBITRARY); break;
  }
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.print(value, DEC);
  Serial.println();
}

void OnPitchChange(byte channel, int pitch) {
  float freqMult = pitch / 16383.0 - 0.5;
  float pitchBend = pow(2, freqMult * 2 / 12);
  waveform1.frequency(currentFreq * pitchBend);
  Serial.println(pitchBend);
  Serial.print("Pitch Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", pitch=");
  Serial.print(pitch, DEC);
  Serial.println();
}

void setup() {
  //Serial.begin(115200);

  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandlePitchChange(OnPitchChange);

  AudioMemory(260);
  waveform1.begin(1.0, 220, WAVEFORM_SAWTOOTH);
  envelope1.attack(5);
  filter1.frequency(1000.0);
  filter1.octaveControl(1.0);
  filter1.resonance(0.7);
  delay1.delay(0, 125);
  delay2.delay(0, 250);

  mixer1.gain(0, 0.8);
  mixer1.gain(1, 0.2);
  mixer2.gain(0, 0.8);
  mixer2.gain(1, 0.2);

  biquad1.setBandpass(0, 1000, 0.1);
  biquad2.setBandpass(0, 1000, 0.1);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);
  sgtl5000_1.lineOutLevel(1.0);
  sgtl5000_1.lineInLevel(15);
}

void loop() {
  usbMIDI.read();
  if(glideTime > 20.0) {
    updateGlide.callbackPeriodBang(glide);
    //Serial.println("GLIDE");
  }
}
