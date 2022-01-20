#include "RTPMainUnit.hpp"
#include "RTPMusicController.h"
#include "ControlCommand.h"
#include "MIDI.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI2);

RTPMainUnit::RTPMainUnit(){
}

void RTPMainUnit::begin(){  
  Serial.begin(115200);
  Wire.begin();
  display.init();
  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
  chordionKeys.initSetup();
  rtpTrellis.begin(this);
  display.printToScreen("Hey there!", "Chordion!", "FTW!");
}

void RTPMainUnit::update(){
  rtpRotary.callbackFromRotary(this);
  rtpRotary.callbackFromClicks(this);
  vlSensor.callbackThreeAxisChanged(this);
}

void RTPMainUnit::updatePeriodically(){
  rtpTrellis.read();
}

void RTPMainUnit::actOnControlsCallback(ControlCommand callbackCommand){
  // printToScreen(callbackCommand);
  switch(callbackCommand.controlType){
    case THREE_AXIS:
      switch(callbackCommand.commandType){
      case CHANGE_LEFT:
        usbMIDI.sendControlChange(CHANGE_LEFT, map(callbackCommand.value,0,vlSensor.getMaxLimitReading(),0,127), 1);
        MIDI2.sendControlChange(1, map(callbackCommand.value ,0,vlSensor.getMaxLimitReading(),0,127), 1);
        break;
      case CHANGE_CENTER:
        usbMIDI.sendControlChange(CHANGE_CENTER, map(callbackCommand.value,0,vlSensor.getMaxLimitReading(),0,127), 1);
        MIDI2.sendControlChange(7, map(callbackCommand.value,0,vlSensor.getMaxLimitReading(),0,127), 1);
        break;
      case CHANGE_RIGHT:
        usbMIDI.sendControlChange(CHANGE_RIGHT, map(callbackCommand.value,0,vlSensor.getMaxLimitReading(),0,127), 1);
        MIDI2.sendControlChange(74, map(callbackCommand.value,0,vlSensor.getMaxLimitReading(),0,127), 1);
        break;
    }
    break;

    case TRELLIS:
      if(callbackCommand.value < N_NOTES){
        Serial.printf("CALLBACK  %d value:%d\n",callbackCommand.commandType, callbackCommand.value);
        switch (callbackCommand.commandType){
        case PRESSED:{
          PlayedChord playedChord = chordionKeys.playChord(baseNote + callbackCommand.value);
          Serial.printf("PRESSED\n");
          display.printToScreen("PLAY CHORD", String(rootName[callbackCommand.value]), String(chordName[playedChord.chordType]));
          break;
        }
        case RELEASED:
          Serial.printf("RELEASED\n");
          chordionKeys.releaseChord(baseNote + callbackCommand.value);
          break;
        }
      }
      else{
        switch (callbackCommand.commandType){
          case PRESSED:
            chordionKeys.enableChordionKey(callbackCommand.value - N_NOTES);
            break;
          case RELEASED:
            chordionKeys.disableChordionKey(callbackCommand.value - N_NOTES);
            break;
        }
      }
    break;

    case ROTARY:
      switch(callbackCommand.commandType){
        case ROTATING_LEFT:
          baseNote -= N_NOTES;
          break;
        case ROTATING_RIGHT:
          baseNote += N_NOTES;
          break;
      }
      break;
    case PUSH_BUTTON:
    break;
  }
}