#include <Arduino.h>

#define LDR_ANALOG_INPUT 0
/*#define GREEN_PWM_OUTPUT 9
#define RED_PWM_OUTPUT 10
#define BLUE_PWM_OUTPUT 11
*/
void setup() {
  Serial.begin(9600);
  // pinMode(GREEN_PWM_OUTPUT, OUTPUT);
}

void loop() {
  int ldrReading = 1023 - analogRead(LDR_ANALOG_INPUT);
  Serial.println(ldrReading);
  delay(10);
  /*
  if(Serial.available()){
    int value = Serial.parseInt();
    int pwmValue = map(value, 0, 1023, 0, 255);
    analogWrite(GREEN_PWM_OUTPUT, pwmValue);
    Serial.println(pwmValue);
  }
  analogWrite(GREEN_PWM_OUTPUT, int(ldrReading/4.0));
  analogWrite(RED_PWM_OUTPUT, int(ldrReading/4.0));
  analogWrite(BLUE_PWM_OUTPUT, int(ldrReading/4.0));
  */
}