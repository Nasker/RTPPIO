#include <Arduino.h>
#include <IRremote.h>

const uint8_t kIrLed = 2;
IRsend irsend;

const uint32_t codeON = 0xFFE01F;
const uint32_t codeOFF = 0xFF609F;
const uint32_t codeUP = 0xFFA05F;
const uint32_t codeDOWN = 0xFF20DF;

void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  irsend.sendNEC(codeON, 32);
  Serial.print("Note on, ch=");
  Serial.print(channel);
  Serial.print(", note=");
  Serial.print(note);
  Serial.print(", velocity=");
  Serial.println(velocity);
}

void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  irsend.sendNEC(codeOFF, 32);
}

void setup() {
  Serial.begin(115200);
  irsend.begin(kIrLed);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleNoteOff(handleNoteOff);
}

void loop() {
  usbMIDI.read();
}