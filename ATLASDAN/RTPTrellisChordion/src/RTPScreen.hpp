#pragma once

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class RTPScreen{
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
public:
  RTPScreen();
  void begin();
  void print(String firstLine, String secondLine);
};
