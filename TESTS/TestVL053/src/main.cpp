#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "SPI.h"
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int lastMidiValue = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  // Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    // Serial.print("Distance (mm): "); 
    int measurement = measure.RangeMilliMeter;
    if(measurement > 2000) measurement = 0;
    Serial.println(measurement);
    int midiValue = constrain(map(measurement,40,200,0,127),0,127);
    if(lastMidiValue != midiValue){
      usbMIDI.sendControlChange(1,midiValue,1);
      lastMidiValue = midiValue;
    }

  } else {
    Serial.println(0);
  }
    
  //delay(100);
}
