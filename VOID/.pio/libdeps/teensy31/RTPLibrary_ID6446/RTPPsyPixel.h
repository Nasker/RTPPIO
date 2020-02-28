/*
	RTPPsyPixel.h - Class for managing PsyPixels.
	Created by Oscar Martínez Carmona @ RockinTechProjects, October 3, 2018.
*/

#ifndef RTPPsyPixel_h
#define RTPPsyPixel_h

#include "Arduino.h"

#include <Adafruit_NeoPixel.h>

class RTPPsyPixel{
    Adafruit_NeoPixel strip;
    float _freq;
    float _fase;
    int _nPixels;
    int _pixelPin;
    public:
      RTPPsyPixel(int nPixels, int pixelPin);
      void beginStrip();
      void psyColorStrip();
      void blackenStrip();
      void redStrip();
      void greenStrip();
      void blueStrip();
      void whiteStrip();
    private:
      float oscillator (float freq, int fase);
};

#endif