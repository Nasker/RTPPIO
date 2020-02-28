#include "RTPTrellis.hpp"
#include "RTPMainUnit.hpp"
#include "constants.h"

const int convertMatrix[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};

RTPTrellis::RTPTrellis(){
}

void RTPTrellis::begin(){
  trellis.begin(0x70);  // only one
  trellis.clear();
}


void RTPTrellis::callbackFromTrellis(RTPMainUnit* mainClass){
  ControlCommand callbackCommand;
  callbackCommand.controlType = TRELLIS;
    if (trellis.readSwitches()) {
      for (uint8_t i=0; i<numKeys; i++) {
        if (trellis.justPressed(i)) {
          trellis.setLED(i);
          callbackCommand.commandType = PRESSED;
          callbackCommand.value = convertMatrix[i];
          mainClass->actOnControlsCallback(callbackCommand);
          //mainClass->actOnTrellisCallback("PRESSED", convertMatrix[i]);
          //rtpScreen->print("PRESSED", String(i));
        }
        if (trellis.justReleased(i)) {
          trellis.clrLED(i);
          callbackCommand.commandType = RELEASED;
          callbackCommand.value = convertMatrix[i];
          mainClass->actOnControlsCallback(callbackCommand);
          //mainClass->actOnTrellisCallback("RELEASED", convertMatrix[i]);
          //rtpScreen->print("DEPRESSED", String(i));
        }
      }
      trellis.writeDisplay();
    }
}