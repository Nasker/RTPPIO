#include <LinkedList.h>
#include <RTPScene.h>
#define DRUM 0
#define SYNTH 1

class RTPSequencer{
  LinkedList<RTPScene*> Sequencer = LinkedList<RTPScene*>();
  int _NScenes;
public:
    RTPSequencer(int NScenes);
    void playAndMoveSequencer();
    void stopAndCleanSequencer();
    void pauseSequencer();
    void editSceneSequenceBlock(int scene, int sequence, LinkedList<RTPEventNote*> displayedEventsList, int NsequenceBlock);
  private:
    void playNoteOn(RTPEventNotePlus* eventNote);
    void playNoteOff(RTPEventNotePlus* eventNote);
};
