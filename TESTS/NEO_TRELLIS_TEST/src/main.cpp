/*  Test to pass a button press to another function.
  *  Will light up the button on first press, then
  *  turn off on second press.
  */

#include "Wire.h"
#include "SPI.h"
#include "Adafruit_NeoTrellis.h"
Adafruit_seesaw ss( &Wire1 );
Adafruit_NeoTrellis trellis = Adafruit_NeoTrellis(0x2E);

byte key;
bool bState[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return trellis.pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return trellis.pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return trellis.pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}

void keypadEvent() {
  Serial.print("Button "); Serial.print(key); Serial.println(" was pressed");
  bState[key] = !bState[key];
  if (bState[key] == true) {
    trellis.pixels.setPixelColor(key, Wheel(map(key, 0, trellis.pixels.numPixels(), 0, 255)));
  }
  else {
    trellis.pixels.setPixelColor(key, 0);
  }
  trellis.pixels.show();
}


//define a callback for key presses
TrellisCallback blink(keyEvent evt){
  // Check is the pad pressed?
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    key = evt.bit.NUM;
    keypadEvent();
    //Serial.print("Button "); Serial.print(evt.bit.NUM); Serial.println(" was pressed");
  }
  // Turn on/off the neopixels!
  //trellis.pixels.show();
  return 0;
}



void setup() {
  Serial.begin(9600);
  Wire1.begin();
  
  if (!trellis.begin()) {
    Serial.println("Could not start trellis, check wiring?");
    while(1);
  } else {
    Serial.println("NeoPixel Trellis started");
  }

  //activate all keys and set callbacks
  for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }
  for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, Wheel(map(i, 0, trellis.pixels.numPixels(), 0, 255)));
    trellis.pixels.show();
    delay(50);
  }
  for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 0x000000);
    trellis.pixels.show();
    delay(50);
  }
}

void loop() {
  trellis.read();
  //keypadEvent();
  delay(20);
}

