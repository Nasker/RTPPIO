#include "RTPOled.hpp"

RTPOled::RTPOled(){}

void RTPOled::initSetup(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.println(F("RTP FTW, BITCH!"));
    display.display();
    delay(2000);
    Serial.println("End of initSetup!");
}

void RTPOled::printStats(ThreeReadings readings){
    display.clearDisplay();
    display.println(F(readings.sensorReading1));
    display.setCursor(0, 10);
    display.println(F(readings.sensorReading2));
    display.setCursor(0, 20);
    display.println(F(readings.sensorReading3));
    display.display();
}