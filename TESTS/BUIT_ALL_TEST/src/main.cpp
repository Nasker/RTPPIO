#include <Arduino.h>
#include <Wire.h>
#include "SPI.h"
#include "Adafruit_NeoTrellis.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTPThreeAxisVL.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_ADDRESS};
Adafruit_NeoTrellis trellis = Adafruit_NeoTrellis(0x2E);
RTPThreeAxisVL vlSensor;

byte key;
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

void keypadEvent() {
  Serial.print("Button "); Serial.print(key); Serial.println(" was pressed");
  printToScreen("Button " + String(key) + " was pressed", 2);
  bState[key] = !bState[key];
  if (bState[key] == true) {
    trellis.pixels.setPixelColor(key, Wheel(map(key, 0, trellis.pixels.numPixels(), 0, 255)));
  }
  else {
    trellis.pixels.setPixelColor(key, 0);
  }
  trellis.pixels.show();
}


//define a callback for key presses
TrellisCallback blink(keyEvent evt){
  // Check is the pad pressed?
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    key = evt.bit.NUM;
    keypadEvent();
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
    delay(20);
  }
  for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 0x000000);
    trellis.pixels.show();
    delay(20);
  }
}

void loop(){
  vlSensor.callbackThreeAxisChanged(actOnCallbackThreeAxisChanged);
  trellis.read();
}