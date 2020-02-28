#include <Arduino.h>
#include "RTPSmartRange.h"
#include "Constants.h"
#include "FunctionsHeaders.h"

int controlsInputs[N_CONTROLS] = {X_LEFT_INPUT, Y_LEFT_INPUT, Z_LEFT_INPUT,
                                  X_RIGHT_INPUT, Y_RIGHT_INPUT, Z_RIGHT_INPUT};

RTPSmartRange handsArray[N_CONTROLS]{
    RTPSmartRange(X_LEFT_ID, 1, 127, 0, 1023), //id, nZones, maxOutput, minInput, maxInput
    RTPSmartRange(Y_LEFT_ID, 3, 127, 0, 1023),
    RTPSmartRange(Z_LEFT_ID, 1, 127, 0, 1023),
    RTPSmartRange(X_RIGHT_ID, 1, 127, 0, 1023),
    RTPSmartRange(Y_RIGHT_ID, 1, 127, 0, 1023),
    RTPSmartRange(Z_RIGHT_ID, 3, 127, 0, 1023),
};

void setup(){
  Serial.begin(115200);
}

void loop(){
  for (int i = 0; i < N_CONTROLS; i++){
    handsArray[i].getCurrentStep(analogRead(controlsInputs[i]));
    handsArray[i].stepChanged(actOnRangeCallback);
  }
}

void actOnRangeCallback(int id, String callbackString, int currentStep, int currentZone){
  Serial.printf("ID: %d, current step: %d in zone %d\n", id, currentStep, currentZone);
  switch(id){
    case  Y_LEFT_ID:
    case  Z_RIGHT_ID:
      if(currentZone == ACTIVE_ZONE)
        usbMIDI.sendControlChange(id, currentStep, MIDI_CHANNEL);
      break;
    default:
      usbMIDI.sendControlChange(id, currentStep, MIDI_CHANNEL);
      break;
  }  
}