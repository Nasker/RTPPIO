#pragma once


struct RTPSequenceNoteStates{
  bool val[16];
};

struct RTPSequenceState{
  bool state;
  int color;
};

struct RTPSequencesState{
  RTPSequenceState sequenceState[16];
};