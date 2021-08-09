#include <Arduino.h>
#include <RTPSequencer.h>

RTPSequencer Sequencer(1);

void setup(){
	Serial.begin(9600);
	Serial.println("Hello!" );
}

void loop() {
	Sequencer.playAndMoveSequencer();
	delay(60);
}
