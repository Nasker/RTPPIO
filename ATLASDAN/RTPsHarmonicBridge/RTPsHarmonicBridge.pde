import themidibus.*; //Import the library

MidiBus busBuit; //The first MidiBus
MidiBus busEtharp; //The first MidiBus
MidiBus busVoid; //The second MidiBus

int backgroundColor = 0;

void setup() {
  size(400, 400);
  MidiBus.list();

  busEtharp = new MidiBus(this, "CHORDION_MIDI", "Teensy MIDI", "etharpBus");
  busBuit = new MidiBus(this, "CHORDION_MIDI", "BUIT_MIDI", "buitBus"); //The first MidiBus;
  colorMode(HSB,100,100,100);
}

void draw(){
  background(map(backgroundColor,0,11,0,100),100,100);
}

void controllerChange(int channel, int number, int value, long timestamp, String bus_name) {
 /* println();
  println("Controller Change:");
  println("--------");
  println("Channel:"+channel);
  println("Number:"+number);
  println("Value:"+value);
  println("Timestamp:"+timestamp);
  println("Recieved on Bus:"+bus_name);
  if (bus_name == "busA") {
    println("This came from IncomingA");
  } else if (bus_name == "busB") {
    println("This came from IncomingB or IncomingC");
  }*/
  busEtharp.sendControllerChange(channel, number, value);
  busBuit.sendControllerChange(channel, number, value);
  backgroundColor = number;
}
