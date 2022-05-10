#include "NotesPlayer.hpp"

NotesPlayer::NotesPlayer(){
    _notesQueue = queue<RTPEventNotePlus>();
    _ringingNotes = vector<std::map<int, RTPEventNotePlus>>(16);
}

void NotesPlayer::queueNote(RTPEventNotePlus note){
    _notesQueue.push(note);
}

void NotesPlayer::playNotes(){
    while(!_notesQueue.empty()){
        RTPEventNotePlus note = _notesQueue.front();
        _notesQueue.pop();
        auto ans = _ringingNotes[note.getMidiChannel()-1].
        insert( std::pair<int, RTPEventNotePlus>(note.getEventNote(), note) );
        if(ans.second)
            note.playNoteOn();
        else
            ans.first->second.playNoteOff();    }
}

void NotesPlayer::decreaseTimeToLive(){
    std::map<int, RTPEventNotePlus>::iterator it;
    for(int i = 0; i < _ringingNotes.size(); i++){
        for(it = _ringingNotes[i].begin(); it != _ringingNotes[i].end(); it++){
            if(!it->second.decreaseTimeToLive())
                _ringingNotes[i].erase(it);
        }    
    }
}

bool NotesPlayer::killThatNote(RTPEventNotePlus note){
    std::map<int, RTPEventNotePlus>::iterator it;
    it = _ringingNotes[note.getMidiChannel()-1].find(note.getEventNote());
    if(it != _ringingNotes[note.getMidiChannel()-1].end()){
        it->second.playNoteOff();
        _ringingNotes[note.getMidiChannel()-1].erase(it);
        return true;
    }
    return false;
}

void NotesPlayer::killAllNotes(){
    std::map<int, RTPEventNotePlus>::iterator it;
    for(int i = 0; i < _ringingNotes.size(); i++){
        for(it = _ringingNotes[i].begin(); it != _ringingNotes[i].end(); it++){
            it->second.playNoteOff();
        }
        _ringingNotes[i].clear();
    }
    while(!_notesQueue.empty())
        _notesQueue.pop();
}