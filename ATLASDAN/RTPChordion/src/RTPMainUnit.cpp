#include "RTPMainUnit.hpp"
#include "RTPMusicController.h"
#include "ControlCommand.h"
#include "MIDI.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI2);

RTPMainUnit::RTPMainUnit(){
}

void RTPMainUnit::begin(){  
  Serial.begin(9600);
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop foreve
  }

  Wire1.begin();
  vlSensor.initSetup();
  //vlSensor.startContinuous();
  chordionKeys.initSetup();
  #ifdef NEO_TRELLIS
    Serial.println("NEO TRELLIS!");
    rtpTrellis.begin(this);
  #else 
  Serial.println("OLD TRELLIS!");
    rtpTrellis.begin();
  #endif
  //machineManager.connectDevices(rtpScreen);
}

void RTPMainUnit::update(){
  rtpRotary.callbackFromRotary(this);
  rtpRotary.callbackFromClicks(this);
}

void RTPMainUnit::updatePeriodically(){
  #ifdef NEO_TRELLIS
    rtpTrellis.read();
  #else 
    rtpTrellis.callbackFromTrellis(this);
  #endif
}

void RTPMainUnit::actOnControlsCallback(ControlCommand callbackCommand){
  printToScreen(callbackCommand);
  switch(callbackCommand.controlType){
    case THREE_AXIS:
      switch(callbackCommand.commandType){
      case CHANGE_LEFT:
        //usbMIDI.sendControlChange(0, map(callbackCommand.value,0,1000,0,127), 1);
        MIDI2.sendControlChange(1, map(callbackCommand.value ,0,1000,0,127), 1);
        break;
      case CHANGE_CENTER:
        //usbMIDI.sendControlChange(1, map(callbackCommand.value,0,1000,0,127), 1);
        MIDI2.sendControlChange(7, map(callbackCommand.value,0,1000,0,127), 1);
        break;
      case CHANGE_RIGHT:
        //usbMIDI.sendControlChange(2, map(callbackCommand.value,0,1000,0,127), 1);
        MIDI2.sendControlChange(74, map(callbackCommand.value,0,1000,0,127), 1);
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
          //rtpScreen.print(String(rootName[callbackCommand.value]), String(chordName[playedChord.chordType]));
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

void RTPMainUnit::printToScreen(ControlCommand command){
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("->ID: " + String(command.controlType));
  display.setCursor(0, 20);
  display.println("->CMD: " + String(command.commandType));
  display.setCursor(0, 40);
  display.println("->VAL: " + String(command.value));
  display.display();
}
