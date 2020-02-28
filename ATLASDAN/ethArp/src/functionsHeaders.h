#pragma once

#include "Arduino.h"

void midiSend(int channel, int midiNote, int velocity);
void scalesChange(String callbackString);
void rootChange(String callbackString);
void readPingArray(String callbackString);
void RealTimeSystem(byte realtimebyte);
void internalClock(String callbackString);
void ultraCalc(int counter);
void noticeBang(String bang);
void printToScreen(String firstLine, String secondLine, boolean salute);