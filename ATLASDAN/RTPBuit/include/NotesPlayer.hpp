#pragma once

#include "RTPEventNotePlus.h"
#include "Arduino.h"
#include <map>
#include <queue>

using namespace std;

class NotesPlayer {
    queue<RTPEventNotePlus> _notesQueue; 
    std::map<int, RTPEventNotePlus> _ringingNotes;
public:
    NotesPlayer();
    void queueNote(RTPEventNotePlus note);
    void playNotes();
    void decreaseTimeToLive();
    bool killThatNote(RTPEventNotePlus note);
    void killAllNotes();
private:
    int keyToNote(RTPEventNotePlus note);
};