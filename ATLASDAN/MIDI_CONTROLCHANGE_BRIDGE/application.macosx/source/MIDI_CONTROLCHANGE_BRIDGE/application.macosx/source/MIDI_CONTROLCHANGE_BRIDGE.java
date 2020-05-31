import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import themidibus.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MIDI_CONTROLCHANGE_BRIDGE extends PApplet {

 //Import the library

MidiBus chordionVoidBus; // The MidiBus
MidiBus chordionEtharpBus;

boolean blinkLed = false;

public void setup() {
  
  background(0, 255, 0);
  MidiBus.list(); 
  chordionVoidBus = new MidiBus(this, "CHORDION_MIDI", "VOID_MIDI"); 
  chordionEtharpBus = new MidiBus(this, "CHORDION_MIDI", "ethArp MIDI");
}

public void draw() {
  background(0);
  if (blinkLed) {
    fill(0, 255, 0);
    println("BLINK");
    ellipse(width/2, height/2, width, height);
    delay(500);
    blinkLed = false;
  }
}

public float oscillator(float freq) {
  float osc = sin((millis()/1000.0f)*freq*TWO_PI)+0.5f;
  return osc;
}

public void controllerChange(int channel, int number, int value) {
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

  public void settings() {  size(100, 100); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MIDI_CONTROLCHANGE_BRIDGE" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
