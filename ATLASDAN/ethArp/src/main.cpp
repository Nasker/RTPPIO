#include <Arduino.h>
#include "functionsHeaders.h"
#include <RTPMusicController.h>
#include <RTPPeriodicBang.h>
#include <RTPRotaryClick.h>
#include <RTPSmartRange.h>

#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
  "The ethArp"
  Sketch for programming the firmware of the ethArp.
  Oscar Martinez Carmona - june/august 2014
 */
/////////////////////"MACROS"///////////////////////

boolean internalClockState = false;
int rootNoteNumber = 0; //C=0,D=2;E=4;F=5;G=7;A=9;B=11; (sostinguts +1..)

int scaleNumber =11;   //1-Ionian/2-Dorian/3-Phrygian/4-Lydian/5-Mixolydian
//6-Aeolian/7-Locrian/8-Harmonic Minor/9-Spanish Gipsy
//10-Hawaian/11-Blues/12-Japanese

int chordNumber = 4; //minor as default

float Tempo = 80.0;
#define MAX_DISTANCE 50
#define MIN_DISTANCE 5
#define SONAR_NUM    2

#define CLOCK 248
#define START 250
#define CONTINUE 251
#define STOP 252 

RTPMusicController mControl;
RTPSmartRange xRange(1, 7, 1000.0), yRange(6, 12, 1000.0);
RTPSmartRange xControlRange(1, 127, 1000.0), yControlRange(1, 127, 1000.0);

RTPRotaryClick scalesButton(0,0,7,HIGH,false), rootButton(0,0,4,HIGH,false);
RTPPeriodicBang periodicRefresh(20);
RTPPeriodicBang periodicBang(((60.0 / Tempo) / 24.0) * 1000);

NewPing sonar[SONAR_NUM] = {
  NewPing(2, 3, MAX_DISTANCE),
  NewPing(0, 1, MAX_DISTANCE)
};

uint_fast16_t xUltraPast, yUltraPast;
boolean lightOn = true;

unsigned int sonarReadings[SONAR_NUM]; 
int ultraReading[SONAR_NUM];
boolean over[SONAR_NUM] = {false,false};

LiquidCrystal_I2C lcd(0x27, 16, 2);

int figure = 0;

int counter = 0;

int arpMode=0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setDelay(0, 0);
  mControl.setMidiChannel(1);
  mControl.setCurrentRootNote(rootNoteNumber);
  mControl.setCurrentScale(scaleNumber);
  mControl.setCurrentChord(chordNumber);
  yRange.setNumberStepsInZone(mControl.scales.getSteps());
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
  usbMIDI.setHandleControlChange(OnControlChange);
  printToScreen(" Hey There!", " I'm the Etharp", true);
  delay(2000);
  printToScreen(mControl.getScaleName(), mControl.getCurrentRootNoteName(), false);
}

void loop() {
 // periodicBang.callbackPeriodBang(internalClock);
  if (internalClockState) periodicBang.callbackPeriodBang(internalClock);
  else usbMIDI.read();
  
  periodicRefresh.callbackPeriodBang(readPingArray);
  scalesButton.callbackOnClicks(scalesChange);
  rootButton.callbackOnClicks(rootChange); 

  if (xUltraPast != xRange.getCurrentStepInZone(ultraReading[0])) {
    usbMIDI.sendControlChange(mControl.getCurrentRootNote(), xControlRange.getCurrentStepInZone(ultraReading[0]), mControl.getMidiChannel());
    xUltraPast = xRange.getCurrentStepInZone(ultraReading[0]);
  }

  if (yUltraPast != yRange.getCurrentStepInZone(ultraReading[1])) {
    usbMIDI.sendControlChange(mControl.getCurrentRootNote() + 12, yControlRange.getCurrentStepInZone(ultraReading[1]), mControl.getMidiChannel());
    yUltraPast = yRange.getCurrentStepInZone(ultraReading[1]);
  }

}

void scalesChange(String callbackString) {
  if (callbackString == "SINGLE click") {
    int currentScale = mControl.getCurrentScale();
    currentScale++;
    if (currentScale > 12) currentScale = 0;
    mControl.setCurrentScale(currentScale);
    printToScreen(mControl.getScaleName(), mControl.getCurrentRootNoteName(), false);
  }
  if (callbackString == "DOUBLE click") {
    internalClockState = !internalClockState;
    lcd.backlight();
  }
}

void rootChange(String callbackString) {
  if (callbackString == "SINGLE click") {
    int currentRoot = mControl.getCurrentRootNote();
    currentRoot++;
    if (currentRoot > 11) 
      currentRoot = 0;
    mControl.setCurrentRootNote(currentRoot);
    printToScreen(mControl.getScaleName(), mControl.getCurrentRootNoteName(), false);
  }
  if (callbackString == "DOUBLE click") {
    arpMode++;
    if(arpMode > ARP_CHORD)
      arpMode = SCALE;
    printToScreen(mControl.getChordName(), mControl.getCurrentRootNoteName(), false);
  }
  if (callbackString == "LONG click") {
    internalClockState = !internalClockState;
    lcd.backlight(); 
  }
}

void readPingArray(String callbackString){
   for(int i=0; i<SONAR_NUM;i++){
     int uS = sonar[i].ping();
     if(uS == 0) over[i] =false;
     else over[i] = true;
     uS = constrain(uS,MIN_DISTANCE*50,MAX_DISTANCE*50);
     uS = map(uS,MIN_DISTANCE*50,MAX_DISTANCE*50,0,1000);
     ultraReading[i] = uS;
     /*
     Serial.print(i);
     Serial.print("   ");
     Serial.print(uS);
     Serial.print("       ");
     */
   }
   //Serial.println();
}

void RealTimeSystem(byte realtimebyte) {
  if (realtimebyte == CLOCK) counter++;
  if (counter == 96)  counter = 0;
  ultraCalc(counter);
  if (counter % 12 == 0) {
    lightOn = !lightOn;
    if (lightOn) lcd.backlight();
    else lcd.noBacklight();
  }
  if (realtimebyte == START || realtimebyte == CONTINUE) {
    lcd.backlight();
    lightOn = true;
    counter = 0;
  }
  if (realtimebyte == STOP) {
    lcd.backlight();
    counter = 0;
  }
}

void OnControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.print(value, DEC);
  Serial.println();
  if(channel == 1 && control>=0 && control<=15 && value>=0 && value<=15){ 
    mControl.setCurrentRootNote(control);
    mControl.setCurrentScale(value);
    mControl.setCurrentChord(value);
    //yRange.setNumberStepsInZone(mControl.chords.getChordSteps());
    yRange.setNumberStepsInZone(mControl.chords.getArpChordSteps());
    Serial.print(mControl.getCurrentRootNoteName());
    Serial.print("\t");
    Serial.println(mControl.getChordName());
  }
}

void ultraCalc(int counter) {
  if (over[0] && over[1]) { //
    mControl.setCurrentOctave(yRange.getCurrentZone(ultraReading[1]));
    mControl.setCurrentStep(yRange.getCurrentStepInZone(ultraReading[1]));
    mControl.setCurrentChordStep(yRange.getCurrentStepInZone(ultraReading[1]));
    mControl.setCurrentArpChordStep(ultraReading[1]);
    figure = xRange.getCurrentStepInZone(ultraReading[0]);
    int mod = (96 - counter) % round(pow(2, figure - 1) * 3);
    if (mod == 0) noticeBang("Bang");
  }
  else midiSend(mControl.getMidiChannel(), mControl.getLastNote(), 0);
}

void noticeBang(String bang) {
  midiSend(mControl.getMidiChannel(), mControl.getLastNote(), 0);
  //midiSend(mControl.getMidiChannel(), mControl.getCurrentMidiNote(), mControl.getVelocity());
  switch(arpMode){
    case SCALE:{
      midiSend(mControl.getMidiChannel(), mControl.getCurrentScaleMidiNote(), mControl.getVelocity());
      mControl.setLastNote(mControl.getCurrentScaleMidiNote());
      break;
    }
    case ARP_CHORD:{
      midiSend(mControl.getMidiChannel(), mControl.getCurrentArpChordMidiNote(), mControl.getVelocity());
      mControl.setLastNote(mControl.getCurrentArpChordMidiNote());
      break;
    }
    case FULL_CHORD:{
      midiSend(mControl.getMidiChannel(), mControl.getCurrentChordMidiNote(), mControl.getVelocity());
      mControl.setLastNote(mControl.getCurrentChordMidiNote());
      break;
    }
  }
  
}

void midiSend(int channel, int midiNote, int velocity) {
  if (velocity != 0)  usbMIDI.sendNoteOn(midiNote, velocity, channel);
  else  usbMIDI.sendNoteOff(midiNote, velocity, channel);
}

void printToScreen(String firstLine, String secondLine, boolean salute) {
  lcd.clear();
  if (!salute) lcd.print("Scale:");
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  if (!salute) lcd.print("Root:");
  lcd.print(secondLine);
}

void internalClock(String callbackString) {
  RealTimeSystem(CLOCK); 
}