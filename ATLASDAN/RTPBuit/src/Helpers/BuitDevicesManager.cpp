#include "BuitDevicesManager.hpp"

BuitDevicesManager::BuitDevicesManager(){}

void BuitDevicesManager::initSetup(){
    _oled.init();
    initBuitSD();
}

void BuitDevicesManager::connectNeoTrellis(const RTPNeoTrellis& neoTrellis){
    _neoTrellis = (RTPNeoTrellis*) &neoTrellis;
}

void BuitDevicesManager::connectSequencer(const RTPSequencer& sequencer){
    _sequencer = (RTPSequencer*) &sequencer;
}

void BuitDevicesManager::connectMusicManager(const MusicManager& musicManager){
    _sequencer->connectMusicManager(musicManager);
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

void BuitDevicesManager::editCurrentNote(ControlCommand command){
    _sequencer->editNoteInCurrentPosition(command);
}

void BuitDevicesManager::changeScene(ControlCommand command){
    switch(command.commandType){
        case ROTATING_RIGHT:
            _sequencer->increaseSelectedScene();
            break;
        case ROTATING_LEFT:
            _sequencer->decreaseSelectedScene();
            break;
    }
    presentScene();
}

void  BuitDevicesManager::nudgePage(ControlCommand command){
    _sequencer->nudgePageInSelectedSequence(command);
    writeSequenceToNeoTrellis(_sequencer->getSelectedSequenceNoteStates(), _sequencer->getSelectedSequenceColor());
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

void BuitDevicesManager::presentBuitCC(){
    printToScreen("Buit CCs", "", "");
    _neoTrellis->writeBuitCCStates(_matrixBuitCC.getBuitCCStates(), TRANSPORT_COLOR);
}

void BuitDevicesManager::selectScene(ControlCommand command){
    _sequencer->selectScene(command.value);
}

void BuitDevicesManager::selectSequence(ControlCommand command){
    _sequencer->selectSequence(command.value);
}

void BuitDevicesManager::editBuitCC(ControlCommand command){
    _matrixBuitCC.toggleBuitCC(command.value);
    _neoTrellis->writeBuitCCStates(_matrixBuitCC.getBuitCCStates(), TRANSPORT_COLOR);
}

void BuitDevicesManager::sendBuitCC(ControlCommand command){
    _matrixBuitCC.updateAndSend(command);
}

void BuitDevicesManager::dumpSequencesToJson(){
    _sequencer->dumpSequencesToJson();
}