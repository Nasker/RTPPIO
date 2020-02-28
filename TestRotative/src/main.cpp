#include <Arduino.h>
#include "RTPButton.h"
#include "RTPRotary.h"

#define ROT_RIGHT_PIN 4
#define ROT_LEFT_PIN 3

RTPButton right(1, ROT_RIGHT_PIN, NORMAL);
RTPButton left(2, ROT_LEFT_PIN, NORMAL);
RTPRotary rotary(0, ROT_RIGHT_PIN, ROT_LEFT_PIN);

void actOnClicks(int ID, String callbackString){
  Serial.printf("ID%d:%s\n", ID, String(callbackString));
}

void actOnRotation(int ID, String callbackString, int a, int b){
  Serial.println(callbackString);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  //right.callback(actOnClicks);
  //left.callback(actOnClicks);
  rotary.callbackOnRotation(actOnRotation);
}