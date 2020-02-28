#include <RTPSoftPot.h>

RTPSoftPot tira(0);

void setup(){
  Serial.begin(9600);
}

void loop(){
  tira.callbackPress(calledBackAction);
}

void calledBackAction(String callbackMessage){
  Serial.println(callbackMessage);
}
