#include "ThreeAxisPing.h"

ThreeAxisPing::ThreeAxisPing(){
}

void ThreeAxisPing::readPingArray() {
  for (int i = 0; i < SONAR_NUM; i++) {
    int uS = sonar[i].ping();
    if (uS == 0) over[i] = false;
    else over[i] = true;
    uS = constrain(uS, MIN_DISTANCE * 50, MAX_DISTANCE * 50);
    uS = map(uS, MIN_DISTANCE * 50, MAX_DISTANCE * 50, 0, 1000);
    ultraReading[i] = uS;
  }
}

bool ThreeAxisPing::overLeft(){
  return over[LEFT];
}

bool ThreeAxisPing::overCenter(){
  return over[CENTER];
}

bool ThreeAxisPing::overRight(){
  return over[RIGHT];
}

int ThreeAxisPing::pingLeft(){
  return ultraReading[LEFT];
}

int ThreeAxisPing::pingCenter(){
  return ultraReading[CENTER];
}

int ThreeAxisPing::pingRight(){
  return ultraReading[RIGHT];
}
