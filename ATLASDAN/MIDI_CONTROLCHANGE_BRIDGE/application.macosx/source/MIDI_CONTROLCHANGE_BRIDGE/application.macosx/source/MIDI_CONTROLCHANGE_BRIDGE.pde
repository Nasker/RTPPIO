import themidibus.*; //Import the library

MidiBus chordionVoidBus; // The MidiBus
MidiBus chordionEtharpBus;

boolean blinkLed = false;

void setup() {
  size(100, 100);
  background(0, 255, 0);
  MidiBus.list(); 
  chordionVoidBus = new MidiBus(this, "CHORDION_MIDI", "VOID_MIDI"); 
  chordionEtharpBus = new MidiBus(this, "CHORDION_MIDI", "ethArp MIDI");
}

void draw() {
  background(0);
  if (blinkLed) {
    fill(0, 255, 0);
    println("BLINK");
    ellipse(width/2, height/2, width, height);
    delay(500);
    blinkLed = false;
  }
}

float oscillator(float freq) {
  float osc = sin((millis()/1000.0)*freq*TWO_PI)+0.5;
  return osc;
}

void controllerChange(int channel, int number, int value) {
  // Receive a controllerChange
  println();
  println("Controller Change:");
  println("--------");
  println("Channel:"+channel);
  println("Number:"+number);
  println("Value:"+value);
  chordionVoidBus.sendControllerChange(channel, number, value);
  chordionEtharpBus.sendControllerChange(channel, number, value);
  blinkLed = true;
}
