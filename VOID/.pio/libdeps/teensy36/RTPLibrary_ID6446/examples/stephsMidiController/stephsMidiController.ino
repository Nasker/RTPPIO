#include <RTPNkButton.h>  //Include RTP's Nk Library
#include <MIDI.h>       //Include HIDUINO Library

MIDI_CREATE_DEFAULT_INSTANCE();    //Instantiate the MIDI Library

#define N_BUTTONS 4      //Number of buttons macro

const int buttonInput[] = {2, 5, 8, 11};    //array containning buttons input port number
const int midiNumber[] = {80, 81, 82, 83};  //array containning midi numbers we want to sent
const int midiChannel = 1;  //midi Channel value (as constant)

RTPNkButton buttons[] = {          //Array of RTPNkButtons, constructor called definning input port
  RTPNkButton(buttonInput[0], YELLOW),     //and COLOR (YELLOW, RED, GREEN or NO_COLOR
  RTPNkButton(buttonInput[1], RED),
  RTPNkButton(buttonInput[2], GREEN),
  RTPNkButton(buttonInput[3], YELLOW)
};

void setup(){    
  Serial.begin(9600);
  MIDI.begin();      //Begin MIDI interface
  for(int i=0; i< N_BUTTONS; i++){  //Loop to initialize buttons values and set each to Orange Light    
    buttons[i].initializeButton(midiChannel, midiNumber[i]);
  }
}

void loop(){
  for(int i=0; i< N_BUTTONS; i++){                   //Loop to detect callbacks from the 
    buttons[i].buttonCallback(sendMidiMessages);     //buttons and insert the below routine
  }
}

             
void sendMidiMessages(String callbackString, int midiChannel, int midiNumber,int velocity){
  if(callbackString == "PRESSED"){ 
    MIDI.sendControlChange(midiNumber,velocity,midiChannel);
  }
  else if (callbackString == "RELEASED"){
    //whatever you might wanna do when you release the button
  }
}  //based on the arguments received throught the callback from the object each call to this routine
   //sends the appropiate message. "PRESSED" and "RELEASED" labels can be used to perform differently
