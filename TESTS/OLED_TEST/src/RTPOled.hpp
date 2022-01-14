#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

struct ThreeReadings {
  int sensorReading1;
  int sensorReading2;
  int sensorReading3;
};

class RTPOled {
    Adafruit_SSD1306* display;
public:
    RTPOled();
    void initSetup();
    void printStats(ThreeReadings readings);
};