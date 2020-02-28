#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define R1_CONTR  91 
#define R2_CONTR  93
#define R3_CONTR  74
#define R4_CONTR  71
#define R5_CONTR  73
#define R6_CONTR  75
#define R7_CONTR  72
#define R8_CONTR  10
#define VOL_CONTR  7
#define MOD_WHEEL  1

AudioInputI2S            i2s1;           //xy=230.28564453125,689.2381591796875
AudioEffectBitcrusher    bitcrusher1;    //xy=522.4999694824219,845.8332824707031
AudioEffectBitcrusher    bitcrusher2;    //xy=525,559.9999694824219
AudioEffectFreeverb      freeverb1;      //xy=551.6666564941406,663.3333282470703
AudioEffectFreeverb      freeverb2;      //xy=551.6665954589844,720.8333435058594
AudioMixer4              mixer2;         //xy=705,920.8333129882812
AudioMixer4              mixer1;         //xy=714.9999389648438,543.3332595825195
AudioFilterStateVariable filter2;        //xy=886,784
AudioFilterStateVariable filter1;        //xy=893,622
AudioOutputI2S           i2s2;           //xy=1035.6190795898438,716.2620239257812
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
AudioConnection          patchCord2(i2s1, 0, freeverb1, 0);
AudioConnection          patchCord3(i2s1, 0, bitcrusher2, 0);
AudioConnection          patchCord4(i2s1, 1, mixer2, 0);
AudioConnection          patchCord5(i2s1, 1, freeverb2, 0);
AudioConnection          patchCord6(i2s1, 1, bitcrusher1, 0);
AudioConnection          patchCord7(bitcrusher1, 0, mixer2, 2);
AudioConnection          patchCord8(bitcrusher2, 0, mixer1, 2);
AudioConnection          patchCord9(freeverb1, 0, mixer2, 1);
AudioConnection          patchCord10(freeverb2, 0, mixer1, 1);
AudioConnection          patchCord11(mixer2, 0, filter2, 0);
AudioConnection          patchCord12(mixer1, 0, filter1, 0);
AudioConnection          patchCord13(filter2, 0, i2s2, 1);
AudioConnection          patchCord14(filter1, 0, i2s2, 0);
AudioControlSGTL5000     sgtl5000_1;     

const int myInput = AUDIO_INPUT_LINEIN;

void OnControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change, ch=");
  switch (control) {
    case R1_CONTR:
      freeverb1.roomsize(value/127.0);
      freeverb2.roomsize(value/127.0);
      break;
    case R2_CONTR:  
      freeverb1.damping(value/127.0);
      freeverb2.damping(value/127.0);
      break;
    case R3_CONTR:
      mixer2.gain(1, value/127.0);
      mixer1.gain(1, value/127.0);
      break;
    case R4_CONTR:
      bitcrusher1.bits(16*(value/127.0));
      bitcrusher2.bits(16*(value/127.0));
    break;
    case R5_CONTR:
      bitcrusher1.sampleRate(44100*(value/127.0));
      bitcrusher2.sampleRate(44100*(value/127.0));
      break;
    case R6_CONTR:  
      filter2.frequency(16000 * pow(constrain(value,0,125) / 127.0, 4));
      filter1.frequency(16000 * pow(constrain(value,0,125) / 127.0, 4));
      break;
    case R7_CONTR:  
      filter2.resonance(5*(value/127.0));
      filter1.resonance(5*(value/127.0));
      break;
    case R8_CONTR:  break;
    case VOL_CONTR: 
      float volume = value/127.0;
      sgtl5000_1.volume(volume);
      Serial.printf("-Volume value: %f\n",volume);
      break;
    case MOD_WHEEL: break;
  }
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.print(value, DEC);
  Serial.println();
}

void setup() {
  AudioMemory(120);
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(1);
  sgtl5000_1.lineOutLevel(13);
  mixer2.gain(0, 1.0);
  mixer1 .gain(0, 1.0);
  mixer2.gain(1, 0.25);
  mixer1 .gain(1, 0.25);
  mixer2.gain(2, 1.0);
  usbMIDI.setHandleControlChange(OnControlChange);
}

void loop() {
  usbMIDI.read();
}