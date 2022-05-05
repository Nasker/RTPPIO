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
    void queueNotes(RTPEventNotePlus note);
    void playNotes();
    void decreaseTimeToLive();
    bool killThatNote(int keyToNote);
    void killAllNotes();
};