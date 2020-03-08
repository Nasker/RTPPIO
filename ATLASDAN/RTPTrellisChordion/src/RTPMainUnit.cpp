#include "RTPMainUnit.hpp"
#include "RTPMusicController.h"
#include "VoidStateMachine.h"
#include "ControlCommand.h"
#include "MIDI.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI2);

VoidState* initState;
VoidStateMachine voidStateMachine(initState);

RTPMainUnit::RTPMainUnit(){
}

void RTPMainUnit::begin(){
  Serial.begin(115200);
  /*rtpTrellis = new RTPTrellis();
  rtpTrellis->begin();*/
  
  rtpRotary = new RTPRotaryClickChordion(ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true);
  threeAxisRange = new ThreeAxisRange();

  rtpScreen = new RTPScreen();
  rtpScreen->begin();
  rtpScreen->print("   Hey There!   ", "  I'm a Test!!  ");
  chordionKeys.initSetup();

  rtpNeotrellis = new RTPNeoTrellis();
  rtpNeotrellis->begin(this);
}

void RTPMainUnit::update(){
  rtpRotary->callbackFromRotary(this);
  rtpRotary->callbackFromClicks(this);
}

void RTPMainUnit::updatePeriodically(){
  threeAxisRange->callbackFromThreeAxis(this);
  rtpNeotrellis->read();
}

void RTPMainUnit::actOnControlsCallback(ControlCommand callbackCommand){
  
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
          rtpScreen->print(String(rootName[callbackCommand.value]), String(chordName[playedChord.chordType]));
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
      switch(callbackCommand.commandType){
        case SINGLE_CLICK:
          voidStateMachine.singleClick();
          break;
        case DOUBLE_CLICK:
          voidStateMachine.doubleClick();
          break;
        case TRIPLE_CLICK:
          voidStateMachine.tripleClick();
          break;
        case LONG_CLICK:
          voidStateMachine.longClick();
          break;
      }
    break;
  }
}