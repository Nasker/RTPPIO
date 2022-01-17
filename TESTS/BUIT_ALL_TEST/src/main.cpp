#include <Arduino.h>
#include <Wire.h>
#include "SPI.h"
#include "Adafruit_NeoTrellis.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTPRotaryClick.h"
#include "RTPThreeAxisVL.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define TRELLIS_ADDRESS 0x2E


#define ROT_LEFT_PIN 11
#define ROT_RIGHT_PIN 12
#define BTN_PIN 10

#define TRELLIS_ID 4
#define BUTTON_ID 5
#define ROTARY_ID 6


Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS};
Adafruit_NeoTrellis trellis = Adafruit_NeoTrellis(TRELLIS_ADDRESS);
RTPRotaryClick rotary(ROT_LEFT_PIN, ROT_RIGHT_PIN, BTN_PIN, false, true);
RTPThreeAxisVL vlSensor;

bool bState[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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

void keypadEvent(int keyNumber) {
  ControlCommand command;
  command.controlID = TRELLIS_ID;
  command.commandType = 0;
  command.value = keyNumber;
  printToScreen(command);
  Serial.print("Button "); Serial.print(keyNumber); Serial.println(" was pressed");
  bState[keyNumber] = !bState[keyNumber];
  if (bState[keyNumber] == true) {
    trellis.pixels.setPixelColor(keyNumber, Wheel(map(keyNumber, 0, trellis.pixels.numPixels(), 0, 255)));
  }
  else {
    trellis.pixels.setPixelColor(keyNumber, 0);
  }
  trellis.pixels.show();
}


//define a callback for key presses
TrellisCallback blink(keyEvent evt){
  // Check is the pad pressed?
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    keypadEvent( evt.bit.NUM);
    //Serial.print("Button "); Serial.print(evt.bit.NUM); Serial.println(" was pressed");
  }
  // Turn on/off the neopixels!
  //trellis.pixels.show();
  return 0;
}

void actOnCallbackThreeAxisChanged(ControlCommand callbackCommand){
  Serial.printf("-ID: %d\t\t-CMD: %d\t\t-Value:%d\n", callbackCommand.controlID, callbackCommand.commandType, callbackCommand.value);
  int midiValue = map(callbackCommand.value, 0, vlSensor.getMaxLimitReading(), 0, 127);
  usbMIDI.sendControlChange(callbackCommand.commandType, midiValue, callbackCommand.controlID);
  printToScreen(callbackCommand);
}

void actOnClicksCallback(String callbackString){
  Serial.println(callbackString);
  ControlCommand command;
  command.controlID = BUTTON_ID;
  if (callbackString == "SINGLE click") 
    command.commandType = 0;
  else if (callbackString == "DOUBLE click")
    command.commandType = 1;
  else if (callbackString == "SINGLE LONG click")
    command.commandType = 2;
  else
    command.commandType = -1;
  command.value = 0;
  printToScreen(command);
}

void actOnRotationCallback(String callbackString, int callbackInt){
  Serial.println(callbackString);
  ControlCommand command;
  command.controlID = ROTARY_ID;
  if (callbackString == "ROTATING LEFT") 
    command.commandType = 0;
  else if (callbackString == "ROTATING RIGHT")
    command.commandType = 1;
  else
    command.commandType = -1;
  command.value = callbackInt;
  printToScreen(command);
}

void setup(){
  Serial.begin (115200);
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop foreve
  }

  if (!trellis.begin()) {
    Serial.println("Could not start trellis, check wiring?");
    while(1);
  } else {
    Serial.println("NeoPixel Trellis started");
  }

  Wire1.begin();
  vlSensor.initSetup();
  vlSensor.startContinuous();
  printToScreen("BUIT DEV TEST!", 2);

  for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }
  for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, Wheel(map(i, 0, trellis.pixels.numPixels(), 0, 255)));
    trellis.pixels.show();
    delay(40);
  }
  for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 0x000000);
    trellis.pixels.show();
    delay(40);
  }
}

void loop(){
  vlSensor.callbackThreeAxisChanged(actOnCallbackThreeAxisChanged);
  trellis.read();
  rotary.callbackOnClicks(actOnClicksCallback);
  rotary.callbackOnRotation(actOnRotationCallback);
}