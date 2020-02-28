#include <Arduino.h>


#define LED_PIN 13

// Teensyduino MIDI Beat Clock Example
// by Sebastian Tomczak
// 29 August 2011

byte CLOCK = 248;
byte START = 250;
byte CONTINUE = 251;
byte STOP = 252;
int counter=0;

void RealTimeSystem(byte realtimebyte) {
  if(realtimebyte == CLOCK) {
    counter++;
    if(counter == 24) {
      counter = 0;
      //digitalWrite(11, HIGH);
      usbMIDI.sendNoteOn(45, 100, 1);
      digitalWrite(LED_PIN,HIGH);
    }

    if(counter == 12) {
     // digitalWrite(11, LOW);
      usbMIDI.sendNoteOff(45,100,1);
      digitalWrite(LED_PIN,LOW);
    }

  }

  if(realtimebyte == START || realtimebyte == CONTINUE) {
    counter = 0;
   // digitalWrite(11, HIGH);
  }

  if(realtimebyte == STOP) {
   // digitalWrite(11, LOW);
   counter = 0;
  }

}

void setup() {
  Serial.begin(9600);
  //pinMode(11, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
}

void loop() {
  usbMIDI.read();
}
