#include <RTPEventNote.h>

class RTPEventNotePlus: public RTPEventNote{
    int _midiChannel;
  public:
    RTPEventNotePlus(int midiChannel, bool state, int note, int velocity):RTPEventNote(state, note, velocity){
      _midiChannel = midiChannel;
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
