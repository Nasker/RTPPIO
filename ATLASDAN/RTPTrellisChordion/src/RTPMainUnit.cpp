#include "RTPMainUnit.hpp"
#include "RTPMusicController.h"
#include "VoidStateMachine.h"
#include "ControlCommand.h"
#include "MIDI.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI2);

VoidState* initState;
VoidStateMachine voidStateMachine(initState);

Adafruit_NeoTrellis myTrellis;

RTPMainUnit::RTPMainUnit(){
}


TrellisCallback blink(keyEvent evt){  
  String evtString;
  if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING){
    myTrellis.pixels.setPixelColor(evt.bit.NUM, 0xFFFFFF); //on rising
    usbMIDI.sendNoteOn(64+evt.bit.NUM, 100, 1);
    Serial.printf("KEY #%d RISES\n", evt.bit.NUM);
  }
    
  else if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING){
    myTrellis.pixels.setPixelColor(evt.bit.NUM, 0); //off falling
    usbMIDI.sendNoteOff(64+evt.bit.NUM, 0, 1);
    Serial.printf("KEY #%d FALLS\n", evt.bit.NUM);
  }
  myTrellis.pixels.show();
  
  return 0;
}

void RTPMainUnit::begin(){
  Serial.begin(115200);
  rtpTrellis = new RTPTrellis();
  rtpTrellis->begin();
  
  //rtpNeotrellis->begin();
  rtpRotary = new RTPRotaryClickChordion(ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true);
  threeAxisRange = new ThreeAxisRange();
  rtpScreen = new RTPScreen();

  rtpScreen->begin();
  rtpScreen->print("   Hey There!   ", "  I'm a Test!!  ");
  chordionKeys.initSetup();

  if(!myTrellis.begin()){
    Serial.println("could not start trellis");
    while(1);
  }
  else
    Serial.println("trellis started");

  for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
    myTrellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    myTrellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    myTrellis.registerCallback(i, blink);
  }
}

void RTPMainUnit::update(){
  rtpRotary->callbackFromRotary(this);
  rtpRotary->callbackFromClicks(this);
}

void RTPMainUnit::updatePeriodically(){
  threeAxisRange->callbackFromThreeAxis(this);
  rtpTrellis->callbackFromTrellis(this);
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