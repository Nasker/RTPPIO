/*
	RTPPsyPixel.cpp - Class for managing PsyPixels.
	Created by Oscar Martínez Carmona @ RockinTechProjects, October 3, 2018.
*/


#include "Arduino.h"
#include "RTPPsyPixel.h"

RTPPsyPixel::RTPPsyPixel(int nPixels, int pixelPin) {
  _nPixels = nPixels;
  _pixelPin = pixelPin;
  strip = Adafruit_NeoPixel(_nPixels , _pixelPin, NEO_GRB + NEO_KHZ800);
}

void RTPPsyPixel::beginStrip() {
  strip.begin();
}

void RTPPsyPixel::psyColorStrip() {
  for (int i = 0; i < _nPixels; i++) {
    strip.setPixelColor(i, strip.Color(255 * oscillator(0.11, i + 1), 255 * oscillator(0.13, i + 1), 255 * oscillator(0.15, i + 1), 50));
  }
  strip.show();

}

void RTPPsyPixel::blackenStrip() {
  for (int i = 0; i < _nPixels; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
  }
  strip.show();
}

void RTPPsyPixel::redStrip() {
  for (int i = 0; i < _nPixels; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0, 50));
  }
  strip.show();
}

void RTPPsyPixel::greenStrip() {
  for (int i = 0; i < _nPixels; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0, 50));
  }
  strip.show();
}

void RTPPsyPixel::blueStrip() {
  for (int i = 0; i < _nPixels; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255, 50));
  }
  strip.show();
}

void RTPPsyPixel::whiteStrip() {
  for (int i = 0; i < _nPixels; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255, 50));
  }
  strip.show();

}

float RTPPsyPixel::oscillator (float freq, int fase) {
  return (1 + (sin(  (TWO_PI / float(fase))  * millis() * (freq / 1000)))) / 2;
}

