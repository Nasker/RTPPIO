#include <Arduino.h>
#include <NewPing.h>
//#include <NewTone.h>
#include <Servo.h>

Servo myservo; 
#define TRIG_PIN 2
#define ECHO_PIN 3
#define MAX_DISTANCE 200
#define BUZZ_PIN 6
#define LED_PIN 9
#define SERVO_PIN 10

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT); 
  myservo.attach(SERVO_PIN); 
}

void loop() {
  int pingTime = sonar.ping();
  if(pingTime)  {
    int freq = map(pingTime, 0, 6000, 220, 880);
    //tone(BUZZ_PIN, freq);
    int pwmLED = map(pingTime, 0, 6000, 0, 255);
    analogWrite(LED_PIN, pwmLED);
    myservo.write(0);  
  }
  else{
    //noTone(BUZZ_PIN);
    analogWrite(LED_PIN, 0);
    analogWrite(SERVO_PIN, 0);
    myservo.write(180); 
    delay(500);
  }
  delay(30);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
}