#include <Arduino.h>
#include "RTPPiezoSensi.hpp"

#define N_PIEZOS 16

RTPPiezoSensi piezoArray[N_PIEZOS]={ 
  RTPPiezoSensi(0, 10, 35), RTPPiezoSensi(1, 10, 36), RTPPiezoSensi(2, 10, 37), RTPPiezoSensi(3, 10, 38), 
  RTPPiezoSensi(4, 10, 39), RTPPiezoSensi(5, 10, 40), RTPPiezoSensi(6, 10, 41), RTPPiezoSensi(7, 10, 42), 
  RTPPiezoSensi(8, 10, 43), RTPPiezoSensi(9, 10, 44), RTPPiezoSensi(10, 10, 45), RTPPiezoSensi(11, 10, 46),
  RTPPiezoSensi(12, 10, 47), RTPPiezoSensi(13, 10, 48), RTPPiezoSensi(14, 10, 49), RTPPiezoSensi(15, 10, 50)
};

void actOnPiezoCallback(int note, int velocity, int channel){
  usbMIDI.sendNoteOn(note, velocity, channel);
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2500)
  Serial.println("Piezo Peak Capture");
}

void loop() {
  for(RTPPiezoSensi piezo:piezoArray)
    piezo.peakDetect(actOnPiezoCallback);
  while(usbMIDI.read()){}
}