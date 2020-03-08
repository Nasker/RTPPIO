import themidibus.*; //Import the library

MidiBus myBus; // The MidiBus

void setup() {
  size(100,100);
  background(0,255,0);
  MidiBus.list(); 
  myBus = new MidiBus(this, "CHORDION_MIDI", "VOID_MIDI"); 
}

void draw() {
  background(0);
  fill(0,255*oscillator(1.0),0);
  ellipse(width/2, height/2,width,height);
}

float oscillator(float freq){
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
  myBus.sendControllerChange(channel, number, value);
}
