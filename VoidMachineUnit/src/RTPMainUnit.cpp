#include "RTPMainUnit.hpp"

//MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
//RTPScreen* rtpScreen = new RTPScreen();


RTPMainUnit::RTPMainUnit(){
}

void RTPMainUnit::begin(){
  Serial.begin(115200);
  //rtpTrellis = new RTPTrellis();
  //MIDI.begin(MIDI_CHANNEL_OMNI);
  //rtpTrellis->begin();
  //rtpScreen->begin();
  //rtpScreen->print("   Hey There!   ", "  I'm a Test!!  ");
}

void RTPMainUnit::update(){
  //rtpTrellis->callbackFromTrellis(this);
}

void RTPMainUnit::actOnTrellisCallback(String callbackString, int buttonNumber){
  if(callbackString == "PRESSED"){

  }
  if(callbackString == "RELEASED"){

  }
}
