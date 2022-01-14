#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTPThreeAxisVL.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS};
RTPThreeAxisVL vlSensor;

void printToScreen(ControlCommand command){
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("->ID: " + String(command.controlID));
  display.setCursor(0, 20);
  display.println("->CMD: " + String(command.commandType));
  display.setCursor(0, 40);
  display.println("->VAL: " + String(command.value));
  display.display();
}

void printToScreen(String text, int size){
  display.clearDisplay();
  display.setTextSize(size); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();      // Show initial text
}

void actOnCallbackThreeAxisChanged(ControlCommand callbackCommand){
  Serial.printf("-ID: %d\t\t-CMD: %d\t\t-Value:%d\n", callbackCommand.controlID, callbackCommand.commandType, callbackCommand.value);
  int midiValue = map(callbackCommand.value, 0, vlSensor.getMaxLimitReading(), 0, 127);
  usbMIDI.sendControlChange(callbackCommand.commandType, midiValue, callbackCommand.controlID);
  printToScreen(callbackCommand);
}

void setup(){
  Serial.begin (115200);
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop foreve
  }
  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
  printToScreen("RTP Three Axis VL", 2);
}

void loop(){
  vlSensor.callbackThreeAxisChanged(actOnCallbackThreeAxisChanged);
}