#pragma once

#include "RTPEventNotePlus.h"
#include "RTPParameter.hpp"
#include "NotesPlayer.hpp"
#include "MusicManager.hpp"
#include "Arduino.h"
#include <vector>
#include "Structs.h"
#include "ControlCommand.h"
#include "constants.h"

using namespace std;

#define SEQ_BLOCK_SIZE 16
#define SCENE_BLOCK_SIZE 16

enum SequenceParametersIndex{
	TYPE,
	MIDI_CHANNEL,
	COLOR
};

class RTPEventNoteSequence{
	vector<RTPEventNotePlus> EventNoteSequence;
	vector<RTPParameter> sequenceParameters;
	NotesPlayer* _notesPlayer;
	MusicManager* _musicManager;
	int _baseNote;
	bool _isEnabled;
	bool _isRecording;
	size_t _currentPosition;
	int _selectedParameter;
public:
	RTPEventNoteSequence(int midiChannel, int NEvents, int type, int baseNote);
	void connectNotesPlayer(const NotesPlayer& notesPlayer);
	void connectMusicManager(const MusicManager& musicManager);
	void fordwardSequence();
	void backwardSequence();
	void resetSequence();
	int getCurrentSequencePosition();
	bool isCurrentSequenceEnabled();
	void enableSequence(bool state);
	RTPEventNotePlus* getCurrentEventNote();
	void playCurrentEventNote();
	void setMidiChannel(int midiChannel);
	int getMidiChannel();
	void setColor(int color);
	int getColor();
	void setType(int type);
	int getType();
	int getSequenceSize();
	void editNoteInSequence(size_t position, bool eventState);
	bool getNoteStateInSequence(size_t position);
	void editNoteInSequence(size_t position, int note, int velocity);
	void editNoteInCurrentPosition(ControlCommand command);
	void resizeSequence(size_t newSize);
	void selectParameter(int parameterIndex);
	void increaseParameterValue();
	void decreaseParameterValue();
	int getParameterValue();
};
