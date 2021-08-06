#include "Arduino.h"

#define IDLE_STATE 0
#define PEAK_TRACKING_STATE 1

class RTPPiezoSensi{
int _analogPin;
int _channel;  // General MIDI: channel 10 = percussion sounds
int _note;     // General MIDI: note 38 = acoustic snare

int thresholdMin = 60;  // minimum reading, avoid noise and false starts
int peakTrackMillis = 12;
int aftershockMillis = 25; // aftershocks & vibration reject

public:
    RTPPiezoSensi(int analogPin, int channel, int note);
    void setThreshold(int threshold);
    void peakDetect(void(*userFunc)(int,int,int));
};