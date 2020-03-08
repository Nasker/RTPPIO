/////////////////////"MACROS"///////////////////////
int rootNoteNumber = 6; //C=0,D=2;E=4;F=5;G=7;A=9;B=11; (sostinguts +1..)

int scaleNumber = 8;   //1-Ionian/2-Dorian/3-Phrygian/4-Lydian/5-Mixolydian
//6-Aeolian/7-Locrian/8-Harmonic Minor/9-Spanish Gipsy
//10-Hawaian/11-Blues/12-Japanese

int chordNumber = 4; //minor as default

float Tempo = 120.0;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_Trellis.h"
#include <RTPPeriodicBang.h>
#include <RTPEventNote.h>
#include <RTPMusicController.h>
#include <RTPSmartRange.h>
#include <RTPRotaryClick.h> 
#include <Encoder.h>
#include <EEPROM.h>
#include <MIDI.h>
#include "LinkedList.h"

#include "ThreeAxisPing.h"
#include "functions.h"
#include "constants.h"

const byte midiChannels[SEQUENCED_LAYERS] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 1, 2, 3, 4};
const byte midiNotes[SEQUENCED_LAYERS] =    {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 90, 90, 90, 90};
const String layerNames[NLayers] = {"PATTERN     Kick", "PATTERN  SUBCONT", "PATTERN    Snare",
                                    "PATTERN     Clap", "PATTERN  SnareII", "PATTERN   KickII",
                                    "PATTERN  OPHiHat", "PATTERN   Hi Tom", "PATTERN  CLHihat",
                                    "PATTERN   LOOP_1", "PATTERN   LOOP_2", "PATTERN    SLICE",
                                    "PATTERN     BASS", "PATTERN   KeysII", "PATTERN  KeysIII",
                                    "PATTERN   KeysIV", "ENABLE     PARTS", "CHORD/KEY SELECT"};

RTPRotaryClick rotaryClick(ROT_LEFT_PIN, ROT_RIGHT_PIN, BUTTON_PIN, LOW, true);
ThreeAxisPing threeAxis;

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

LiquidCrystal_I2C lcd(0x27, 16, 2);

RTPPeriodicBang periodicBang(((60.0 / Tempo) / 24.0) * 1000);
//IntervalTimer periodicBang;
RTPPeriodicBang periodicRefresh(20), periodicRefresh2(20);// periodicRefresh3(100);
RTPMusicController mControl;
RTPSmartRange leftRange(4, 12, 1000.0), centerRange(1, 1, 127, 0, 1000.0), rightRange(0, 1, 127, 0, 1000.0), drumRollRange(1, 11 , 1000.0);
const int rows = 4, cols = 4;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

struct Matrix {
  RTPEventNote matrix[4][4] = {
    {RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0)},
    {RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0)},
    {RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0)},
    {RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0), RTPEventNote(false, 0)}
  };
  byte noteMode;
  byte midiChannel;
  int midiNote;
  int lastMidiNote;
  LinkedList<int> lastChordNotes;
};

Matrix sequenceMatrix[NLayers];
int activeLayer = ENABLE_PART_LAYER;
int pastLayer = activeLayer;

byte counter = 0;
byte clockGrid = 6;

boolean internalClockState = false;
boolean selectLayerWMatrixState = false;

byte currentRow = 0;
byte currentCol = 0;
byte lastPosition = 0;

void setup() {
  Serial.begin(115200);
  loadEprom();
  lcd.init();
  lcd.backlight();
  printToScreen("   Hey There!   ", "VOID IN DA HOUSE");
  mControl.setCurrentRootNote(rootNoteNumber);
  mControl.setCurrentScale(scaleNumber);
  mControl.setCurrentChord(chordNumber);
  leftRange.setNumberStepsInZone(mControl.scales.getSteps());
  MIDI.begin(MIDI_CHANNEL_OMNI);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
  usbMIDI.setHandleProgramChange(OnProgramChange);
  usbMIDI.setHandleControlChange(OnControlChange);
  // periodicBang.begin(internalClock, ((60.0 / Tempo) / 24.0) * 1000000);
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);
  initSequence();
  refreshKeypad();
  printToScreen(layerNames[activeLayer], "Roll   CC0   CC1");
}

void loop() {
  if (internalClockState) periodicBang.callbackPeriodBang(internalClock);
  else {
    usbMIDI.read();
    MIDI.read();
  }

  rotaryClick.callbackOnRotation(actOnRotCallback);
  rotaryClick.callbackOnClicks(manageButtonClicks);

  periodicRefresh.callbackPeriodBang(readKeypad);
  periodicRefresh2.callbackPeriodBang(linkReadPingArrayCallback);

  if(threeAxis.overRight()){
    rightRange.getCurrentStep(threeAxis.pingRight());
    rightRange.stepChanged(actOnRangeCallback);
  }
  if(threeAxis.overCenter()){
    centerRange.getCurrentStep(threeAxis.pingCenter());
    centerRange.stepChanged(actOnRangeCallback);
  }
}

void actOnRangeCallback(int id, String callbackString, int currentStep, int currentZone) {
  //Serial.printf("-ID: %d \t%s  \tstep: %d \n", id, callbackString, currentStep);
  usbMIDI.sendControlChange(id, currentStep, sequenceMatrix[activeLayer].midiChannel);
}

void manageButtonClicks(String callbackString){
  if(callbackString=="DOUBLE click"){
    if(activeLayer == ENABLE_PART_LAYER)
      activeLayer = KEY_SELECT_LAYER;
    else 
      activeLayer = ENABLE_PART_LAYER;
    rotaryClick.write(activeLayer * 4);
    refreshKeypad();
    printToScreen(layerNames[activeLayer], "Roll   CC0   CC1");
  }

  if(callbackString == "TRIPLE click") saveOnEprom();

  if(callbackString == "SINGLE LONG click") switchInternalClockState();

  if(callbackString == "SINGLE click") {
    if(activeLayer == ENABLE_PART_LAYER) selectLayerWMatrixState = true;
    else selectLayerWMatrixState = false;
  }
}

void internalClock(String callbackString) { //String callbackString
  RealTimeSystem(CLOCK);
}

void actOnRotCallback(String callbackString, int newPosition){
/* if (newPosition != activeLayer) {
    if (newPosition >= NLayers) {
      newPosition = NLayers - 1;
      rotaryClick.write(newPosition * 4);
    }
    if (newPosition <= 0) {
      newPosition = 0;
      rotaryClick.write(newPosition);
    }
    */
    Serial.print(callbackString);
    Serial.print("\t-Position: ");
    Serial.println(newPosition);
  //}
}

void RealTimeSystem(byte realtimebyte) {
  if (realtimebyte == CLOCK) counter++;
  //Serial.println(counter);
  if (counter == 96) counter = 0;
  int mod = counter % clockGrid;
  if (mod == 0) {
    noticeBang("Bang");
    //Serial.println("BANG");
  }
  if (counter % 12   == 0) {
  }
  int index=0; 
  int rollerValues[4] = {1,2,3,6};
  if(threeAxis.overRight()){
    index = map(constrain(threeAxis.pingRight(),0,500),0,500,0,3);
    //Serial.printf( "RIGHT PING:%d\n", rollerValues[index]);
  }

  if (threeAxis.overRight() && counter % rollerValues[index] == 0 && threeAxis.overLeft() && activeLayer < DRUM_LAYERS) {
    midiSend(sequenceMatrix[0].midiChannel, midiNotes[drumRollRange.getCurrentStepInZone(threeAxis.pingLeft())], 127);//ultraReading[0]
    midiSend(sequenceMatrix[0].midiChannel, midiNotes[drumRollRange.getCurrentStepInZone(threeAxis.pingLeft())], 0);//ultraReading[0]
    //Serial.println(drumRollRange.getCurrentStepInZone(ultraReading[0]));
  }
  if (realtimebyte == START || realtimebyte == CONTINUE) {
    counter = 0;
  }

  if (realtimebyte == STOP) {
    counter = 0;
    currentRow = 0;
    currentCol = 0;
  }
}
void noticeBang(String callbackString) {
  if(activeLayer != pastLayer){
       //printToScreen(layerNames[activeLayer], "Roll   CC0   CC1");
    pastLayer = activeLayer;
  }
  if (sequenceMatrix[activeLayer].matrix[currentRow][currentCol].eventState() && threeAxis.overLeft()) {
    sequenceMatrix[activeLayer].matrix[currentRow][currentCol].setEventRead(threeAxis.pingLeft());
    //mControl.setCurrentOctave(leftRange.getCurrentZone(ultraReading[0]));
    //mControl.setCurrentStep(leftRange.getCurrentStepInZone(ultraReading[0]));
    //sequenceMatrix[activeLayer].matrix[currentRow][currentCol].setEventNote(mControl.getCurrentMidiNote());
  }
  for (int currentLayer = 0; currentLayer < SEQUENCED_LAYERS; currentLayer++) {
    if (sequenceMatrix[currentLayer].matrix[currentRow][currentCol].eventState() && layerIsNotMute(currentLayer)) {
      if (sequenceMatrix[currentLayer].noteMode == DRUM) {
        midiSend(sequenceMatrix[currentLayer].midiChannel, sequenceMatrix[currentLayer].midiNote, 127);
        midiSend(sequenceMatrix[currentLayer].midiChannel, sequenceMatrix[currentLayer].midiNote, 0);
      }
      else if (sequenceMatrix[currentLayer].noteMode == SYNTH) {
        midiSend(sequenceMatrix[currentLayer].midiChannel, sequenceMatrix[currentLayer].lastMidiNote, 0);
        mControl.setCurrentOctave(leftRange.getCurrentZone(sequenceMatrix[currentLayer].matrix[currentRow][currentCol].getEventRead()));
        mControl.setCurrentStep(leftRange.getCurrentStepInZone(sequenceMatrix[currentLayer].matrix[currentRow][currentCol].getEventRead()));
        //mControl.setCurrentScaleStep(leftRange.getCurrentStepInZone(sequenceMatrix[currentLayer].matrix[currentRow][currentCol].getEventRead()));
        mControl.setCurrentChordStep(leftRange.getCurrentStepInZone(sequenceMatrix[currentLayer].matrix[currentRow][currentCol].getEventRead()));
        //midiSend(sequenceMatrix[currentLayer].midiChannel, mControl.getCurrentScaleMidiNote(), 100);
        midiSend(sequenceMatrix[currentLayer].midiChannel, mControl.getCurrentChordMidiNote(), 100);
        //sequenceMatrix[currentLayer].lastMidiNote = mControl.getCurrentScaleMidiNote();
        sequenceMatrix[currentLayer].lastMidiNote = mControl.getCurrentChordMidiNote();
      }
      else if (sequenceMatrix[currentLayer].noteMode == CHORD) {
        mControl.setCurrentOctave(leftRange.getCurrentZone(sequenceMatrix[currentLayer].matrix[currentRow][currentCol].getEventRead()));
        for(int i=0; i< sequenceMatrix[currentLayer].lastChordNotes.size(); i++){
          midiSend(sequenceMatrix[currentLayer].midiChannel, sequenceMatrix[currentLayer].lastChordNotes.get(i), 0);
          sequenceMatrix[currentLayer].lastChordNotes.remove(i);
        }
        for(int i=0; i<mControl.chords.getChordSteps(); i++){
          mControl.setCurrentChordStep(i);
          midiSend(sequenceMatrix[currentLayer].midiChannel, mControl.getCurrentChordMidiNote(), 100);
          sequenceMatrix[currentLayer].lastChordNotes.add(mControl.getCurrentChordMidiNote());
        } 
      }

    }
    else if (sequenceMatrix[currentLayer].matrix[currentRow][currentCol].eventState() && !layerIsNotMute(currentLayer)) {
      midiSend(sequenceMatrix[currentLayer].midiChannel, sequenceMatrix[currentLayer].lastMidiNote, 0);
    }
  }
  fordwardSequencer();
}

void fordwardSequencer() {
  currentRow++;
  if (currentRow > 3) {
    currentRow = 0;
    currentCol++;
    if (currentCol > 3) currentCol = 0;
  }
  refreshKeypad();
  if (activeLayer < ENABLE_PART_LAYER) {
    trellis.setLED(currentRow * cols + currentCol);
    trellis.clrLED(lastPosition);
    trellis.writeDisplay();
  }
  lastPosition = currentRow * cols + currentCol;
}

void refreshKeypad() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (sequenceMatrix[activeLayer].matrix[i][j].eventState())trellis.setLED(i * cols + j);
      else trellis.clrLED(i * cols + j);
    }
  } 
  trellis.writeDisplay();
}

void midiSend(int channel, int midiNote, int velocity) {
  if (velocity != 0) {
    usbMIDI.sendNoteOn(midiNote, velocity, channel);
    MIDI.sendNoteOn(midiNote, velocity, channel);
    //Serial.println("SEND_NOTE");
  }
  else  {
    usbMIDI.sendNoteOff(midiNote, velocity, channel);
    MIDI.sendNoteOff(midiNote, velocity, channel);
  }
}

void printToScreen(String firstLine, String secondLine) {
  lcd.clear();
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}

void initSequence() {
  for (int j = 0; j < 8; j++) {
    for (uint8_t i = 0; i < 16; i++) {
      trellis.setLED(i);
      trellis.writeDisplay();
      delay(16/(j+1));
    }
    for (uint8_t i = 0; i < 16; i++) {
      trellis.clrLED(i);
      trellis.writeDisplay();
      delay(16/(j+1));
    }
  }
  refreshKeypad();
}

void readKeypad(String callbackString) {
  if (trellis.readSwitches()) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (trellis.justPressed(i * cols + j)) {
          if(selectLayerWMatrixState){
            activeLayer = j*cols+i;
            selectLayerWMatrixState = false;
            printToScreen(layerNames[activeLayer], "Roll   CC0   CC1");
          }
          else sequenceMatrix[activeLayer].matrix[i][j].switchState();
        }
      }
    }
    refreshKeypad();
  }
}

void linkReadPingArrayCallback(String callbackString) {
  threeAxis.readPingArray(callbackString);
}

void loadEprom() {
  int address = 0;
  for (int l = 0; l < NLayers; l++) {
    sequenceMatrix[l].midiChannel = midiChannels[l];
    sequenceMatrix[l].midiNote = midiNotes[l];
    if (midiChannels[l] == 10) 
      sequenceMatrix[l].noteMode = DRUM;
    else if (midiChannels[l] == 4) 
      sequenceMatrix[l].noteMode = CHORD;
    else 
      sequenceMatrix[l].noteMode = SYNTH;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        int readValue = EEPROM.read(address);
        sequenceMatrix[l].matrix[i][j].setEventState(readValue != 0);
        sequenceMatrix[l].matrix[i][j].setEventRead(readValue);
        address++;
      }
    }
  }
}
 
void saveOnEprom() {
  Serial.println("Saving on EEPROM");
    int address = 0;
    int actualValue = 0;
    for (int l = 0; l < NLayers; l++) {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if(sequenceMatrix[l].matrix[i][j].eventState()) actualValue = sequenceMatrix[l].matrix[i][j].getEventRead();
          else actualValue = 0;
          EEPROM.write(address, actualValue);
          Serial.print(actualValue);
          Serial.print("\t");
          address++;
           Serial.println(address);
        }
      }
    }
}

void switchInternalClockState() {
    internalClockState = !internalClockState;
    RealTimeSystem(STOP);
    Serial.println("SWITCH TO INTERNAL/EXTERNAL CLOCK");
}

void OnProgramChange(byte channel, byte program) {
    Serial.print("Program Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", program=");
    Serial.print(program, DEC);
    Serial.println();
  /*switch (channel) {
    case 1:
      mControl.setCurrentScale(program);
      Serial.print("Scale Change: ");
      Serial.println(program);
      break;

    case 2:
      mControl.setCurrentRootNote(program);
      Serial.print("Root Change: ");
      Serial.println(program);
      break;
  }*/
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
    leftRange.setNumberStepsInZone(mControl.chords.getChordSteps());
    Serial.print(mControl.getCurrentRootNoteName());
    Serial.print("\t");
    Serial.println(mControl.getChordName());
  }
}

bool layerIsNotMute(int layerNumber) {
  int col = layerNumber / 4;
  int row = layerNumber % 4;
  bool state = sequenceMatrix[ENABLE_PART_LAYER].matrix[row][col].eventState();
  //Serial.println(state);
  return state;
}
/*
void updateScreen(String callbackString){
  printToScreen(layerNames[activeLayer], "Roll   CC0   CC1");
}*/
