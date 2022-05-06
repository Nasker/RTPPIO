 #include <Arduino.h>

#define DEPLOY_VERSION

#define TRELLIS 1
#define ROTARY 2
#define THREE_AXIS 3
#define PUSH_BUTTON 4

#define CHANGE_LEFT 0
#define CHANGE_CENTER 1
#define CHANGE_RIGHT 2

#define ROTATING_LEFT 0
#define ROTATING_RIGHT 1

#define PRESSED 0
#define RELEASED 1

#define SINGLE_CLICK 0
#define DOUBLE_CLICK 1
#define TRIPLE_CLICK 2
#define LONG_CLICK 3

#define BUTTON_PIN 10
#define ROT_LEFT_PIN 11
#define ROT_RIGHT_PIN 12

#if defined(DEPLOY_VERSION)
    #define SENSOR_1_PIN 2
    #define SENSOR_2_PIN 3
    #define SENSOR_3_PIN 4
#elif 
    #define SENSOR_1_PIN 5
    #define SENSOR_2_PIN 6
    #define SENSOR_3_PIN 7
#endif

#define N_NOTES 12
#define BASE_NOTE 48

#define LEFT 0
#define CENTER 1
#define RIGHT 2
