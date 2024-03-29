#include "RTPSequencer.h"

#define CLOCK 248
#define START 250
#define CONTINUE 251
#define STOP 252
#define TICKS_PER_BAR 96
#define CLOCK_GRID 6

class RTPSequencerManager{
    RTPSequencer* _sequencer;
    byte counter;
public:
    RTPSequencerManager();
    void connectSequencer(const RTPSequencer& sequencer);
    void handleRealTimeSystem(byte realtimebyte);
private:
    void gridClockUp(byte realtimebyte);
    void increaseCounter();
    void resetCounter();
};