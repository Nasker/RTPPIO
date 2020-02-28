#include "Adafruit_NeoTrellis.h"
#define N_KEYS 12

Adafruit_NeoTrellis trellis;

const bool pianoArray[N_KEYS] = {1,0,1,0,1,1,0,1,0,1,0,1};
const int convertMatrix[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};

#define INT_PIN 2

void paintPiano(){
  for(uint16_t i=0; i<N_KEYS; i++) {
    trellis.pixels.setPixelColor(convertMatrix[i], pianoArray[convertMatrix[i]]*0xEEEEEE);
    trellis.pixels.show();
  }
}

TrellisCallback blink(keyEvent evt){  
  String evtString;
  if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING){
    trellis.pixels.setPixelColor(evt.bit.NUM, 0xFFFFFF); //on rising
    usbMIDI.sendNoteOn(64+evt.bit.NUM, 100, 1);
    Serial.printf("KEY #%d RISES\n", convertMatrix[evt.bit.NUM]);
    //paintPiano();
  }
    
  else if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING){
    trellis.pixels.setPixelColor(evt.bit.NUM, 0); //off falling
    usbMIDI.sendNoteOff(64+convertMatrix[evt.bit.NUM], 0, 1);
    Serial.printf("KEY #%d FALLS\n", convertMatrix[evt.bit.NUM]);
    //paintPiano();
  }
  trellis.pixels.show();
  
  return 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(INT_PIN, INPUT);
  
  if(!trellis.begin()){
    Serial.println("could not start trellis");
    while(1);
  }
  else{
    Serial.println("trellis started");
  }

  //activate all keys and set callbacks
  for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
    trellis.activateKey(convertMatrix[i], SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(convertMatrix[i], SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(convertMatrix[i], blink);
  }

  //do a little animation to show we're on
  for(uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(convertMatrix[i], 0xF5AA42);
    trellis.pixels.show();
    delay(50);
    trellis.pixels.setPixelColor(convertMatrix[i], 0x000000);
    trellis.pixels.show();
    //delay(50);
  }
  paintPiano();
}

void loop() {
  if(!digitalRead(INT_PIN)){
    trellis.read(false);
  }
  delay(2);
}
