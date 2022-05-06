#include <Arduino.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int myInput = AUDIO_INPUT_LINEIN;
// const int myInput = AUDIO_INPUT_MIC;

// Create the Audio components.  These should be created in the
// order data flows, inputs/sources -> processing -> outputs
//

AudioInputI2S       audioInput;         // audio shield: mic or line-in
AudioOutputI2S      audioOutput;        // audio shield: headphones & line-out

// Create Audio connections between the components

// Just connecting in to out
AudioConnection c1(audioInput, 0, audioOutput, 0); // left connection
AudioConnection c2(audioInput, 1, audioOutput, 1); // right connection

// Create an object to control the audio shield.
// 
AudioControlSGTL5000 audioShield;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(4);
  // Enable the audio shield and set the output volume.
  while(!audioShield.enable()) {
    delay(500);
    Serial.print(".");
  }
  audioShield.inputSelect(myInput);
  audioShield.volume(1.0);
}

void loop() {}