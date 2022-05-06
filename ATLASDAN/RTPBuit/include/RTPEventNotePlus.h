#pragma once

#include <RTPEventNote.h>
#include "Arduino.h"

class RTPEventNotePlus: public RTPEventNote{
    int _midiChannel;
    int _length;
  public:
    RTPEventNotePlus(int midiChannel, bool state, int note, int velocity):RTPEventNote(state, note, velocity){
      _midiChannel = midiChannel;
      _length = 1;
    }
    RTPEventNotePlus(int midiChannel, bool state, int note, int velocity, int length):RTPEventNote(state, note, velocity){
      _midiChannel = midiChannel;
      _length = length;
    }
    int getMidiChannel(){
      return _midiChannel;
    }
    void setMidiChannel(int midiChannel){
      _midiChannel = midiChannel;
    }
    void playNoteOn(){
      usbMIDI.sendNoteOn(getEventNote(), getEventVelocity(), getMidiChannel());
    }
    void playNoteOff(){
      usbMIDI.sendNoteOff(getEventNote(), getEventVelocity(), getMidiChannel());
    }
};
 