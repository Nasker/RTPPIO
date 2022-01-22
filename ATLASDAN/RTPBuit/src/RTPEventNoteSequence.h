#pragma once

#include "LinkedList.h"
#include "RTPEventNotePlus.h"
#include "RTPParameter.hpp"
#include "Arduino.h"

#define SEQ_BLOCK_SIZE 16
#define SCENE_BLOCK_SIZE 16

enum RTPEventNoteSequenceType{
	DRUM,
	BASS_SYNTH,
	MONO_SYNTH,
	POLY_SYNTH
};

enum SequenceParametersIndex{
	TYPE,
	MIDI_CHANNEL,
	COLOR
};

class RTPEventNoteSequence{
	LinkedList<RTPEventNotePlus*> EventNoteSequence = LinkedList<RTPEventNotePlus*>();
	LinkedList<RTPParameter*> sequenceParameters;
	bool _isEnabled;
	bool _isRecording;
	int _currentPosition;
	int _selectedParameter;
public:
	RTPEventNoteSequence(int midiChannel, int NEvents, int type);
	void fordwardSequence();
	void backwardSequence();
	void resetSequence();
	int getCurrentSequencePosition();
	bool isCurrentSequenceEnabled();
	void enableSequence(bool state);
	RTPEventNotePlus* getCurrentEventNote();
	void setMidiChannel(int midiChannel);
	int getMidiChannel();
	void setColor(int color);
	int getColor();
	void setType(int type);
	int getType();
	int getSequenceSize();
	void editNoteInSequence(int position, bool eventState);
	bool getNoteStateInSequence(int position);
	void editNoteInSequence(int position, int note, int velocity);
	void resizeSequence(int newSize);
	void selectParameter(int parameterIndex);
	void increaseParameterValue();
	void decreaseParameterValue();
	int getParameterValue();
};
