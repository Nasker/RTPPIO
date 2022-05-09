#include "NotesPlayer.hpp"

NotesPlayer::NotesPlayer(){
    _notesQueue = queue<RTPEventNotePlus>();
    _ringingNotes = std::map<int, RTPEventNotePlus>();
}

void NotesPlayer::queueNotes(RTPEventNotePlus note){
    _notesQueue.push(note);
}

void NotesPlayer::playNotes(){
    while(!_notesQueue.empty()){
        RTPEventNotePlus note = _notesQueue.front();
        _notesQueue.pop();
        _ringingNotes[note.getMidiChannel()*1000 + note.getEventNote()] = note;
        note.playNoteOn();
    }
}

void NotesPlayer::decreaseTimeToLive(){
    std::map<int, RTPEventNotePlus>::iterator it;
    for(it = _ringingNotes.begin(); it != _ringingNotes.end(); it++){
        if(!it->second.decreaseTimeToLive())
            _ringingNotes.erase(it);
    }    
}

bool NotesPlayer::killThatNote(int keyToNote){
    std::map<int, RTPEventNotePlus>::iterator it;
    it = _ringingNotes.find(keyToNote);
    if(it != _ringingNotes.end()){
        it->second.playNoteOff();
        _ringingNotes.erase(it);
        return true;
    }
    return false;
}

void NotesPlayer::killAllNotes(){
    std::map<int, RTPEventNotePlus>::iterator it;
    for(it = _ringingNotes.begin(); it != _ringingNotes.end(); it++)
        it->second.playNoteOff();
    _ringingNotes.clear();
}