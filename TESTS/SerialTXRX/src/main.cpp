#include <Arduino.h>

void setup() {
    Serial.begin(9600);   // USB Serial
    Serial1.begin(9600);  // Hardware UART (RX/TX)
}

void loop() {
    if (Serial.available()) {
        Serial1.write(Serial.read());  // Forward from USB to UART
    }
    if (Serial1.available()) {
        Serial.write(Serial1.read());  // Forward from UART to USB
    }
}
