#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_Trellis.h"

#define numKeys 16

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);


void setup() {
    trellis.begin(0x70);  // only one
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(20);
  }
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(20);
  }
}

void loop() {
  delay(20);
  if (trellis.readSwitches()) {
    for (uint8_t i=0; i<numKeys; i++) {
	    if (trellis.justPressed(i)) {
	      Serial.print("v"); Serial.println(i);
	      trellis.setLED(i);
	    } 
	    if (trellis.justReleased(i)) {
	      Serial.print("^"); Serial.println(i);
	      trellis.clrLED(i);
	    }
    }
    trellis.writeDisplay();
  }
}