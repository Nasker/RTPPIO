#include <Arduino.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <CircularBuffer.h> // For rolling window

#define SDA_PIN 21
#define SCL_PIN 22

// DC offset removal parameters
#define WINDOW_SIZE 100 // 1 second at 100Hz sampling
#define MIN_IR_VALUE 5000 // Minimum IR value to consider valid data
#define FILTER_SIZE 24 // 24-sample filter for noise reduction

// Peak detection parameters
#define PEAK_THRESHOLD 10 // Minimum value change to consider a peak
#define MIN_PEAK_DISTANCE 30 // Minimum samples between peaks (300ms at 100Hz)

MAX30105 particleSensor;
CircularBuffer<long, WINDOW_SIZE> irBuffer; // Buffer to store IR values
CircularBuffer<long, FILTER_SIZE> filterBuffer; // Buffer for noise filtering
unsigned long lastSampleTime = 0;
const int samplingRate = 10; // Sample every 10ms (100Hz)

// Peak detection variables
long prevValue = 0;
long prevDiff = 0;
long lastPeakTime = 0;
bool wasIncreasing = false;
long lastPeakValue = 0;
unsigned long lastBeatTime = 0;
float beatsPerMinute = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000); // Give serial a moment to initialize
  Serial.println("\n\nInitializing Heart Rate Sensor Test...");
  Serial.println("ESP32 is running!");
  
  // Initialize I2C with specific pins
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000); // Start with slower speed (100kHz)
  
  delay(500);
  Serial.println("I2C initialized");
  
  // Initialize sensor with more debug info
  Serial.println("Attempting to connect to MAX30105 sensor...");
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) // Use standard speed (100kHz)
  {
    Serial.println("MAX30105 was not found. Please check wiring/power.");
    Serial.println("SDA connected to pin: " + String(SDA_PIN));
    Serial.println("SCL connected to pin: " + String(SCL_PIN));
    // Don't hang forever, try again every 3 seconds
    while (1) {
      delay(3000);
      Serial.println("Retrying sensor connection...");
      if (particleSensor.begin(Wire, I2C_SPEED_STANDARD))
        break;
    }
  }
  Serial.println("MAX30105 found!");
  Serial.println("Place your index finger on the sensor with steady pressure.");

  // Configure sensor with default settings
  Serial.println("Setting up sensor...");
  particleSensor.setup(); 
  Serial.println("Setting LED brightness...");
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  Serial.println("Setup complete!");
}

void loop() {
  if (millis() - lastSampleTime >= samplingRate) {
    lastSampleTime = millis();
    long irValue = particleSensor.getIR();

    if (irValue < MIN_IR_VALUE) {
      while (!irBuffer.isEmpty())
        irBuffer.pop();
      while (!filterBuffer.isEmpty())
        filterBuffer.pop();
      return;
    }
    
    // Add to DC offset buffer
    irBuffer.push(irValue);
    
    if (irBuffer.isFull()) {
      // Calculate DC offset (average of buffer)
      long dcOffset = 0;
      for (int i = 0; i < WINDOW_SIZE; i++) {
        dcOffset += irBuffer[i];
      }
      dcOffset /= WINDOW_SIZE;
      
      // Remove DC offset
      long dcRemovedValue = irValue - dcOffset;
      
      // Add to filter buffer for noise reduction
      filterBuffer.push(dcRemovedValue);
      
      // Only process when we have enough samples for filtering
      if (filterBuffer.isFull()) {
        // Apply moving average filter
        long filteredValue = 0;
        for (int i = 0; i < FILTER_SIZE; i++) {
          filteredValue += filterBuffer[i];
        }
        filteredValue /= FILTER_SIZE;
        
        // Peak detection using derivative approach
        long currentDiff = filteredValue - prevValue;
        
        // Check for sign change in the derivative (slope)
        // A peak occurs when slope changes from positive to negative
        if (prevDiff > 0 && currentDiff <= 0) { // We were increasing and now we're decreasing
          // We have a potential peak
          unsigned long currentTime = millis();
          
          // Check if it's a significant peak and enough time has passed since last peak
          if ((filteredValue > lastPeakValue + PEAK_THRESHOLD) && 
              (currentTime - lastPeakTime > MIN_PEAK_DISTANCE * samplingRate)) {
            
            // Calculate BPM based on time between peaks
            if (lastBeatTime != 0) {
              unsigned long beatDuration = currentTime - lastBeatTime;
              beatsPerMinute = 60000.0 / beatDuration; // Convert to BPM (60000ms per minute)
              
              // Only accept reasonable heart rates
              if (beatsPerMinute >= 40 && beatsPerMinute <= 180) {
                // Output the BPM value
                Serial.print("Peak! BPM: ");
                Serial.println(beatsPerMinute);
              }
            }
            
            // Update peak tracking variables
            lastPeakValue = filteredValue;
            lastPeakTime = currentTime;
            lastBeatTime = currentTime;
          }
        }
        
        // Store current values for next iteration
        prevDiff = currentDiff;
        prevValue = filteredValue;
        
        // Output the filtered value
        Serial.println(filteredValue);
      }
    }
  }
}