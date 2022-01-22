#include "BuitOutDevicesManager.hpp"

BuitOutDevicesManager::BuitOutDevicesManager(){

}

void BuitOutDevicesManager::initSetup(){
    _oled.init();
}

void BuitOutDevicesManager::connectNeoTrellis(const RTPNeoTrellis& neoTrellis){
    _neoTrellis = (RTPNeoTrellis*) &neoTrellis;
}

void BuitOutDevicesManager::printToScreen(String firstLine, String secondLine, String thirdLine){
    _oled.printToScreen(firstLine, secondLine, thirdLine);
}

void BuitOutDevicesManager::printToScreen(ControlCommand command){
    _oled.printToScreen(command);
}

void BuitOutDevicesManager::writeSequenceToNeoTrellis(RTPSequenceNoteStates sequenceStates, int color){
    _neoTrellis->writeSequenceStates(sequenceStates, color);
}

void BuitOutDevicesManager::writeSceneToNeoTrellis(RTPSequencesState sequencesState){
    _neoTrellis->writeSceneStates(sequencesState);
}

void BuitOutDevicesManager::writeTransportPage(){
    _neoTrellis->writeTransportPage();
}