#include <NewPing.h>
#include <Arduino.h>
#include "constants.h"

class ThreeAxisPing{
  NewPing sonar[SONAR_NUM] = {
    NewPing(TRIGGER_SONAR_LEFT, ECHO_SONAR_LEFT, MAX_DISTANCE),
    NewPing(TRIGGER_SONAR_CENTER, ECHO_SONAR_CENTER, MAX_DISTANCE),
    NewPing(TRIGGER_SONAR_RIGHT, ECHO_SONAR_RIGHT, MAX_DISTANCE)
  };
  int ultraReading[SONAR_NUM];
  boolean over[SONAR_NUM] = {false, false, false};

  public:
    ThreeAxisPing();
    void readPingArray(String callbackString);
    bool overLeft();
    bool overCenter();
    bool overRight();
    int pingLeft();
    int pingCenter();
    int pingRight();
};
