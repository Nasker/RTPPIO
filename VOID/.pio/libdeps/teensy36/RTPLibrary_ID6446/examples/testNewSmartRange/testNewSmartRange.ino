#include "RTPSmartRange.h"

RTPSmartRange range(2,4);

void setup(){
  Serial.begin(9600);
}

void loop(){
  range.getCurrentStepInZone(analogRead(0));
  range.stepChanged(manageChange);
}

void manageChange(String callbackString, int stepinZone, int zone){
  Serial.print("-Zone: ");
  Serial.print(zone);
  Serial.print("  -Step In Zone: ");
  Serial.print(stepinZone);
  Serial.print("  -Message: ");
  Serial.println(callbackString);
}
