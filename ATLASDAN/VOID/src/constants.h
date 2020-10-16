 #include <Arduino.h>

#define DRUM 0
#define SYNTH 1
#define CHORD 2

#define NPOSITIONS 256
#define MAX_DISTANCE 25
#define MIN_DISTANCE 5
#define SONAR_NUM     3
#define INTPIN A2
#define NLayers 18
#define SEQUENCED_LAYERS 16
#define SCENES 1
#define DRUM_LAYERS 12
#define ENABLE_PART_LAYER NLayers-2
#define KEY_SELECT_LAYER NLayers-1

#define ROT_RIGHT_PIN 4
#define ROT_LEFT_PIN 3
#define BUTTON_PIN 2

#define TRIGGER_SONAR_LEFT 5
#define ECHO_SONAR_LEFT 6
#define TRIGGER_SONAR_CENTER 7
#define ECHO_SONAR_CENTER 8
#define TRIGGER_SONAR_RIGHT 10
#define ECHO_SONAR_RIGHT 12
#define LEFT 0
#define CENTER 1
#define RIGHT 2

#define CLOCK 248
#define START 250
#define CONTINUE 251
#define STOP 252