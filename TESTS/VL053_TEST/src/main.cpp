#include <Arduino.h>
#include "RTPThreeAxisVL.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

RTPThreeAxisVL vlSensor;


void actOnCallbackThreeAxisChanged(ControlCommand callbackCommand){
  Serial.printf("-ID: %d\t\t-CMD: %d\t\t-Value:%d\n", callbackCommand.controlID, callbackCommand.commandType, callbackCommand.value);
  int midiValue = map(callbackCommand.value, 0, vlSensor.getMaxLimitReading(), 0, 127);
  usbMIDI.sendControlChange(callbackCommand.commandType, midiValue, callbackCommand.controlID);
}


void setup(){
  Serial.begin (115200);
  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
}

void loop(){
  vlSensor.callbackThreeAxisChanged(actOnCallbackThreeAxisChanged);
}