#include <Arduino.h>

void manageButtonClicks(String callbackString);

void internalClock(String callbackString);

void internalClockTimer();

void actOnRotCallback(String callbackString, int newPosition);

void RealTimeSystem(byte realtimebyte);

void actOnClockGridTick(String callbackString);

void fordwardSequencer();

void refreshKeypad();

void midiSend(int channel, int midiNote, int velocity);

void printToScreen(String firstLine, String secondLine);

void initSequence();

void readKeypad(String callbackString);

void actOnRangeCallback(int id, String callbackString, int currentStep, int currentZone);

void linkReadPingArrayCallback(String callbackString); //void readPingArray(String callbackString);

void loadEprom();

void saveOnEprom();

void switchInternalClockState();

void OnProgramChange(byte channel, byte program);

void OnControlChange(byte channel, byte control, byte value);

bool layerIsNotMute(int layerNumber);

/*
void updateScreen(String callbackString){
  printToScreen(layerNames[activeLayer], "Roll   CC0   CC1");
}*/
