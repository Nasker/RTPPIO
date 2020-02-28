#include "ThreeAxisRange.hpp"
#include "RTPMainUnit.hpp"

ThreeAxisRange::ThreeAxisRange(){
    threeAxisPing = new ThreeAxisPing();
}

void ThreeAxisRange::callbackFromThreeAxis(RTPMainUnit* mainClass){
    threeAxisPing->readPingArray();
    ControlCommand callbackCommand;
    callbackCommand.controlType = THREE_AXIS;
    if(threeAxisPing->overLeft() && threeAxisPing->pingLeft() != pLeftRange){
        callbackCommand.commandType = CHANGE_LEFT;
        callbackCommand.value = threeAxisPing->pingLeft();
        mainClass->actOnControlsCallback(callbackCommand);
        pLeftRange = threeAxisPing->pingLeft();
    }
    if(threeAxisPing->overCenter() && threeAxisPing->pingCenter() != pCenterRange){
        callbackCommand.commandType = CHANGE_CENTER;
        callbackCommand.value = threeAxisPing->pingCenter();
        mainClass->actOnControlsCallback(callbackCommand);
        pCenterRange = threeAxisPing->pingCenter();
    }
    if(threeAxisPing->overRight() && threeAxisPing->pingRight() != pRightRange){
        callbackCommand.commandType = CHANGE_RIGHT;
        callbackCommand.value = threeAxisPing->pingRight();
        mainClass->actOnControlsCallback(callbackCommand);
        pRightRange = threeAxisPing->pingRight();
    }
}
