#include <Arduino.h>
#include "RTPRotaryClick.h"
#define LEFT_ROT_PIN 11
#define RIGHT_ROT_PIN 12
#define BUTTON_PIN 10

RTPRotaryClick rotaryClick(LEFT_ROT_PIN, RIGHT_ROT_PIN, BUTTON_PIN, false, true);

void actOnCallbackClicks(String command){
  Serial.println(command);
}

void actOnCallbackRotation(ControlCommand callbackCommand){
  Serial.printf("->ID: %d \t->Type: %d  \t->Value:%d\n",callbackCommand.controlID, callbackCommand.commandType, callbackCommand.value);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  rotaryClick.callbackOnClicks(actOnCallbackClicks);
  rotaryClick.callbackOnRotation(actOnCallbackRotation);
}