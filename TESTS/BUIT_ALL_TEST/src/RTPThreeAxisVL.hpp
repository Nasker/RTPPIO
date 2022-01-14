#pragma once

#include <VL53L0X.h>
#include "Wire.h"

#define CONTROL_ID 1

#define SENSOR_1_PIN 5
#define SENSOR_2_PIN 6
#define SENSOR_3_PIN 7

#define SENSOR_1_ID 1
#define SENSOR_2_ID 2
#define SENSOR_3_ID 3

#define DEFAULT_MAX_READING 306
#define DEFAULT_MIN_READING 50

struct ThreeReadings {
  int sensorReading1;
  int sensorReading2;
  int sensorReading3;
};

struct ControlCommand{
  int controlID;
  int commandType;
  int value;
};

class RTPThreeAxisVL{
  VL53L0X sensor1;
  VL53L0X sensor2;
  VL53L0X sensor3;
  ThreeReadings lastReadings;
  int _maxLimitReading;
  int _minLimitReading;
public:
  RTPThreeAxisVL();
  void initSetup();
  void startContinuous();
  void stopContinuous();
  void setMaxLimitReading(int maxReading);
  int getMaxLimitReading();
  void setMinLimitReading(int minReading);
  int getMinLimitReading();
  ThreeReadings getThreeReadings();
  ThreeReadings getThreeCleanReadings();
  void callbackThreeAxisChanged(void (*userFunc) (ControlCommand callbackCommand));
};
