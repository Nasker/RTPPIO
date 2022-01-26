#include "Arduino.h"

#include "SequenceEditState.h"

SequenceEditState::SequenceEditState(BuitStateMachine* buitMachine){
  Serial.println("SequenceEditState");
  _buitMachine = buitMachine;
}

void SequenceEditState::singleClick() {
  Serial.println("Does nothing here!");
}

void SequenceEditState::doubleClick() {
  Serial.println("Going to Scene Edit!");
  _outDevices->printToScreen("State:", "Scene Edit!","");
  _outDevices->writeSceneToNeoTrellis(_sequencer->getSequencesState());
  _buitMachine->setState(_buitMachine->getSceneEditState());
}

void SequenceEditState::longClick() {
  Serial.println("Going to Sequence Settings!");
  _outDevices->printToScreen("State:", "Sequence Settings!","");
  _buitMachine->setState(_buitMachine->getSequenceSettingsState());
}

void SequenceEditState::rotaryTurned(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void SequenceEditState::threeAxisChanged(ControlCommand command) {
  Serial.println("Does nothing here!");
}

void SequenceEditState::trellisPressed(ControlCommand command) {
  _sequencer->toggleNoteInSceneInSelectedSequence(command.value);
  _outDevices->writeSequenceToNeoTrellis(_sequencer->getSelectedSequenceNoteStates(), _sequencer->getSelectedSequenceColor());
}

void SequenceEditState::trellisReleased(ControlCommand command) {
  Serial.println("Does nothing here!");
}