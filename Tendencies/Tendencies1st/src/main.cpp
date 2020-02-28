#include <Arduino.h>
#include "NewTone.h"

#define JOY_X_PIN 0
#define JOY_Y_PIN 1
#define JOY_SW_PIN 4
#define TRIG_PIN 2
#define ECHO_PIN 3
#define BUZZ_PIN 6
#define LED_PIN 9

void setup() {
  Serial.begin(9600);
  pinMode(JOY_SW_PIN, INPUT_PULLUP);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int joyXRead = analogRead(JOY_X_PIN);
  int joyYRead = analogRead(JOY_Y_PIN);

  int freq = map(joyXRead, 0, 1023, 220, 880);

  int pwmValue = map(joyYRead, 0, 1023, 0, 255);

  analogWrite(LED_PIN, pwmValue);

  boolean joySwRead = !digitalRead(JOY_SW_PIN);

  if(joySwRead)
    NewTone(BUZZ_PIN, freq);
  else
    noNewTone(BUZZ_PIN);

  Serial.print(joyXRead);
  Serial.print("\t");
  Serial.print(joyYRead);
  Serial.print("\t");
  Serial.print(joySwRead);
  Serial.print("\t");
  Serial.println(pwmValue);
  delay(10);
}