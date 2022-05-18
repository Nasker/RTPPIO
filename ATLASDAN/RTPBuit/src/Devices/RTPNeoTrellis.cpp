#include "RTPNeoTrellis.hpp"
#include "RTPMainUnit.hpp"


Adafruit_NeoTrellis RTPNeoTrellis::myTrellis;
RTPMainUnit* RTPNeoTrellis::mainUnit;

const int convertMatrix[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};

RTPNeoTrellis::RTPNeoTrellis(){
}

TrellisCallback RTPNeoTrellis::blink(keyEvent evt){  
  String evtString;
  ControlCommand callbackCommand;
  callbackCommand.controlType = TRELLIS;
  if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING){
    //myTrellis.pixels.setPixelColor(evt.bit.NUM, 0xFFFFFF); //on rising
    //Serial.printf("KEY #%d RISES\n", convertMatrix[evt.bit.NUM]);
    callbackCommand.commandType = PRESSED;
    callbackCommand.value = convertMatrix[evt.bit.NUM];//convertMatrix[evt.bit.NUM];
    mainUnit->actOnControlsCallback(callbackCommand);
    //mainClass->actOnControlsCallback(callbackCommand);
  }
    
  else if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING){
    //myTrellis.pixels.setPixelColor(evt.bit.NUM, 0); //off falling
    //Serial.printf("KEY #%d FALLS\n", evt.bit.NUM);
    callbackCommand.commandType = RELEASED;
    callbackCommand.value = evt.bit.NUM;//convertMatrix[evt.bit.NUM];
    mainUnit->actOnControlsCallback(callbackCommand);
    //mainClass->actOnControlsCallback(callbackCommand);
  }
  myTrellis.pixels.show();
  
  return 0;
}

void RTPNeoTrellis::begin(RTPMainUnit* _mainUnit){
  RTPNeoTrellis::mainUnit = _mainUnit;
  if(!myTrellis.begin()){
    Serial.println("could not start trellis");
    while(1);
  }
  else
    Serial.println("trellis started");

  for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
    myTrellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    myTrellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    myTrellis.registerCallback(i, RTPNeoTrellis::blink);
    //Serial.println(i);
  }
}

void RTPNeoTrellis::read(){
  myTrellis.read();
}


void RTPNeoTrellis::writeSequenceStates(RTPSequenceNoteStates seqStates, int color){
  for(int i=0; i<SEQ_BLOCK_SIZE; i++){
    if(seqStates.val[i]){
      myTrellis.pixels.setPixelColor(convertMatrix[i], color);
    }
    else{
      myTrellis.pixels.setPixelColor(convertMatrix[i], 0);
    }
  }
  myTrellis.pixels.show();
}

void RTPNeoTrellis::writeSceneStates(RTPSequencesState sequencesState){
  for(int i=0; i<SCENE_BLOCK_SIZE; i++){
    if(sequencesState.sequenceState[i].state)
      myTrellis.pixels.setPixelColor(convertMatrix[i], sequencesState.sequenceState[i].color);
    else
      myTrellis.pixels.setPixelColor(convertMatrix[i], 0);
  }
  myTrellis.pixels.show();
}

void RTPNeoTrellis::writeTransportPage(int color){
  for(int i=0; i<SCENE_BLOCK_SIZE; i++){
    myTrellis.pixels.setPixelColor(i, color);
  }
  myTrellis.pixels.show();
}

void RTPNeoTrellis::writeBuitCCStates(RTPSequenceNoteStates buitCCStates){
  writeSequenceStates(buitCCStates, TRANSPORT_COLOR);
}

/*
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
}*/