#include "RTPSequencerManager.hpp"

RTPSequencerManager::RTPSequencerManager(){
    resetCounter();
}

void RTPSequencerManager::connectSequencer(const RTPSequencer& sequencer){
    _sequencer = (RTPSequencer*) &sequencer;
}
void RTPSequencerManager::handleRealTimeSystem(byte realtimebyte){
	switch (realtimebyte) {
        case STOP:
            _sequencer->stopAndCleanSequencer();
            resetCounter();
            break;
        case CLOCK:
            gridClockUp(realtimebyte);
            break;
        default:
            // Serial.printf("RealTimeSystem: %d\n", realtimebyte);
            break;
	}
}

void RTPSequencerManager::gridClockUp(byte realtimebyte){
    increaseCounter();
    if (counter % CLOCK_GRID == 0)
        _sequencer->playAndMoveSequencer();
} 

void RTPSequencerManager::increaseCounter(){
    counter++;
    if (counter == TICKS_PER_BAR) 
        resetCounter();
}

void RTPSequencerManager::resetCounter(){
    counter = 0;
}