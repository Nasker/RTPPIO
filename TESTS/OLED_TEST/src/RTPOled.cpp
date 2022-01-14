#include "RTPOled.hpp"

RTPOled::RTPOled(){}

void RTPOled::initSetup(){
    Wire1.begin();
    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, SCREEN_ADDRESS);
    if(!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
}

void RTPOled::printStats(ThreeReadings readings){
    display->clearDisplay();
    display->println(F(readings.sensorReading1));
    display->setCursor(0, 10);
    display->println(F(readings.sensorReading2));
    display->setCursor(0, 20);
    display->println(F(readings.sensorReading3));
    display->display();
}