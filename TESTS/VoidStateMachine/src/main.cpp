#include <Arduino.h>
#include "VoidStateMachine.h"
#include <RTPRotaryClick.h>

#define ROT_RIGHT_PIN 4
#define ROT_LEFT_PIN 3
#define BUTTON_PIN 2

RTPRotaryClick rotaryClick(ROT_RIGHT_PIN, ROT_LEFT_PIN, BUTTON_PIN, LOW, true);
VoidState* initState;
VoidStateMachine voidStateMachine(initState);

void actOnClickCallback(String callbackString) {
  if(callbackString == "SINGLE click"){
    voidStateMachine.singleClick();
  }
  if(callbackString == "DOUBLE click"){
    voidStateMachine.doubleClick();
  }
  if(callbackString == "TRIPLE click"){
    voidStateMachine.tripleClick();
  }

  if(callbackString == "SINGLE LONG click"){
    voidStateMachine.longClick();
  }
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  rotaryClick.callbackOnClicks(actOnClickCallback);
}
