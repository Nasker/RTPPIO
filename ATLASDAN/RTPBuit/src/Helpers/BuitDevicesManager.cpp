#include "BuitDevicesManager.hpp"

BuitDevicesManager::BuitDevicesManager(){}

void BuitDevicesManager::initSetup(){
    _oled.init();
}

void BuitDevicesManager::connectNeoTrellis(const RTPNeoTrellis& neoTrellis){
    _neoTrellis = (RTPNeoTrellis*) &neoTrellis;
}

void BuitDevicesManager::connectSequencer(const RTPSequencer& sequencer){
    _sequencer = (RTPSequencer*) &sequencer;
}

void BuitDevicesManager::printToScreen(String firstLine, String secondLine, String thirdLine){
    _oled.printToScreen(firstLine, secondLine, thirdLine);
}

void BuitDevicesManager::printToScreen(ControlCommand command){
    _oled.printToScreen(command);
}

void BuitDevicesManager::writeSequenceToNeoTrellis(RTPSequenceNoteStates sequenceStates, int color){
    _neoTrellis->writeSequenceStates(sequenceStates, color);
}

void BuitDevicesManager::writeSceneToNeoTrellis(RTPSequencesState sequencesState){
    _neoTrellis->writeSceneStates(sequencesState);
}

void BuitDevicesManager::writeTransportPage(){
    _neoTrellis->writeTransportPage(TRANSPORT_COLOR);
}

void BuitDevicesManager::editScene(ControlCommand command){
    _sequencer->toggleSequence(command.value);
    writeSceneToNeoTrellis(_sequencer->getSequencesState());
}

void BuitDevicesManager::editSequence(ControlCommand command){
    printToScreen("Edit Sequence", "", "");
    _sequencer->toggleNoteInSceneInSelectedSequence(command.value);
    _neoTrellis->writeSequenceStates(_sequencer->getSelectedSequenceNoteStates(), _sequencer->getSelectedSequenceColor());
}

void BuitDevicesManager::presentScene(){
    printToScreen("Edit Scene","","");
    writeSceneToNeoTrellis(_sequencer->getSequencesState());
}

void BuitDevicesManager::presentSequence(){
    printToScreen("Edit Sequence","","");
    writeSequenceToNeoTrellis(_sequencer->getSelectedSequenceNoteStates(), _sequencer->getSelectedSequenceColor());
}

void BuitDevicesManager::presentTransport(){
    printToScreen("Transport", "", "");
    writeTransportPage();
}

void BuitDevicesManager::selectScene(ControlCommand command){
    _sequencer->selectScene(command.value);
}

void BuitDevicesManager::selectSequence(ControlCommand command){
    _sequencer->selectSequence(command.value);
}

