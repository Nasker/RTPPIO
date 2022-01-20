#pragma once

#include "LinkedList.h"
#include "RTPEventNotePlus.h"
#include "Arduino.h"


class RTPEventNoteSequence{
	  LinkedList<RTPEventNotePlus*> EventNoteSequence = LinkedList<RTPEventNotePlus*>();
	  int _midiChannel;
	  int _type;
	  bool _isEnabled;
	  bool _isRecording;
	  int _currentPosition;

	public:
	    RTPEventNoteSequence(int midiChannel, int NEvents, int type);
	    void fordwardSequence();
	    void backwardSequence();
	    void resetSequence();
	    int getCurrentSequencePosition();
	    bool isCurrentSequenceEnabled();
	    int getSequenceType();
	    RTPEventNotePlus* getCurrentEventNote();
	    void setMidiChannel(int midiChannel);
	    int getMidiChannel();
	    void editSequenceBlock(LinkedList<RTPEventNote*> displayedEventsList, int NsequenceBlock);
};
