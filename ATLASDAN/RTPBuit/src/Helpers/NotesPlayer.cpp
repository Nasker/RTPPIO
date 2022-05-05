#include "NotesPlayer.hpp"

NotesPlayer::NotesPlayer(){
    _notesQueue = queue<RTPEventNotePlus>();
    _ringingNotes = std::map<int, RTPEventNotePlus>();
}

void NotesPlayer::queueNotes(RTPEventNotePlus note){

}

void NotesPlayer::playNotes(){

}

void NotesPlayer::decreaseTimeToLive(){

}

bool NotesPlayer::killThatNote(int keyToNote){

}

void NotesPlayer::killAllNotes(){

}