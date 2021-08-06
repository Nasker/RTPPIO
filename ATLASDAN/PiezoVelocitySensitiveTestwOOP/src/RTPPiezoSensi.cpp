#include "RTPPiezoSensi.hpp"

RTPPiezoSensi::RTPPiezoSensi(int analogPin, int channel, int note){
  _analogPin = analogPin;
  _channel = channel;
  _note = note;
};

void RTPPiezoSensi::peakDetect(void(*userFunc)(int,int,int)) {
  // "static" variables keep their numbers between each run of this function
  static int state;  // 0=idle, 1=looking for peak, 2=ignore aftershocks
  static int peak;   // remember the highest reading
  static elapsedMillis msec; // timer to end states 1 and 2
  int voltage = analogRead(_analogPin);
  switch (state) {
    // IDLE state: wait for any reading is above threshold.  Do not set
    // the threshold too low.  You don't want to be too sensitive to slight
    // vibration.
    case IDLE_STATE:
      if (voltage > thresholdMin) {
        //Serial.print("begin peak track ");
        //Serial.println(voltage);
        peak = voltage;
        msec = 0;
        state = PEAK_TRACKING_STATE;
      }
      return;

    // Peak Tracking state: capture largest reading
    case PEAK_TRACKING_STATE:
      if (voltage > peak) {
        peak = voltage;     
      }
      if (msec >= peakTrackMillis) {
        //Serial.print("peak = ");
        //Serial.println(peak);
        int velocity = map(peak, thresholdMin, 1023, 1, 127);
        //usbMIDI.sendNoteOn(_note, velocity, _channel);
        userFunc(_note, velocity, _channel);
        msec = 0;
        state = 2;
      }
      return;

    // Ignore Aftershock state: wait for things to be quiet again.
    default:
      if (voltage > thresholdMin) {
        msec = 0; // keep resetting timer if above threshold
      } else if (msec > aftershockMillis) {
        //usbMIDI.sendNoteOff(_note, 0, _channel);
        userFunc(_note, 0, _channel);
        state = IDLE_STATE; // go back to idle when
      }
  }
}