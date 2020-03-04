#include "RTPNeoTrellis.hpp"
#include "RTPMainUnit.hpp"



const int convertMatrix[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};

//RTPNeoTrellis::RTPNeoTrellis(){
//}

static TrellisCallback blink(keyEvent evt){  
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

void RTPNeoTrellis::begin(){
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

void RTPNeoTrellis::callbackFromNeoTrellis(RTPMainUnit* mainClass){
  ControlCommand callbackCommand;
  callbackCommand.controlType = TRELLIS;
    if (true) {
      for (uint8_t i=0; i<numKeys; i++) {
        if (true){//trellis.justPressed(i)) {
          //trellis.setLED(i);
          callbackCommand.commandType = PRESSED;
          callbackCommand.value = convertMatrix[i];
          mainClass->actOnControlsCallback(callbackCommand);
          //mainClass->actOnTrellisCallback("PRESSED", convertMatrix[i]);
          //rtpScreen->print("PRESSED", String(i));
        }
        if (true){//trellis.justReleased(i)) {
          //trellis.clrLED(i);
          callbackCommand.commandType = RELEASED;
          callbackCommand.value = convertMatrix[i];
          mainClass->actOnControlsCallback(callbackCommand);
          //mainClass->actOnTrellisCallback("RELEASED", convertMatrix[i]);
          //rtpScreen->print("DEPRESSED", String(i));
        }
      }
      //trellis.pixels.show();
    }
}