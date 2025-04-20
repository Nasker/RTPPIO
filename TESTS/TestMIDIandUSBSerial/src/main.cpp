#include <Arduino.h>

#include <MIDI.h>

#define HWSerial Serial1
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI); // 5 Pin DIN Out
const int HWChannel = 16 ;
const int USBChannel = 1;

void setup() 
{  
  HWSerial.begin(31250);
  MIDI.begin();  
}

void loop() {
  int note;
  for (note=48; note <= 60; note++) // Range was changed from 10:127 to save eardrums. 
  {
    usbMIDI.sendNoteOn(note, 100, USBChannel);
    MIDI.sendNoteOn(note, 100, HWChannel);
    delay(500);
    usbMIDI.sendNoteOff(note, 100, USBChannel);
    MIDI.sendNoteOff(note, 100, HWChannel);
  }
}