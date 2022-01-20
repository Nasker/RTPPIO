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
  rtpTrellis.begin(this);
  display.printToScreen("Hey!", "RTPDev!", "In here!");
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
  display.printToScreen(callbackCommand);
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
          Serial.printf("PRESSED\n");
          break;
        }
        case RELEASED:
          Serial.printf("RELEASED\n");
          break;
        }
      }
      else{
        switch (callbackCommand.commandType){
          case PRESSED:
            break;
          case RELEASED:
            break;
        }
      }
    break;

    case ROTARY:
      switch(callbackCommand.commandType){
        case ROTATING_LEFT:
          break;
        case ROTATING_RIGHT:
          break;
      }
      break;
    case PUSH_BUTTON:
    break;
  }
}