#include "RTPThreeAxisVL.hpp"

RTPThreeAxisVL::RTPThreeAxisVL(){
    _maxLimitReading = DEFAULT_MAX_READING;
    _minLimitReading = DEFAULT_MIN_READING;
}

void RTPThreeAxisVL::initSetup(){
    pinMode(SENSOR_1_PIN, OUTPUT);
    pinMode(SENSOR_2_PIN, OUTPUT);
    pinMode(SENSOR_3_PIN, OUTPUT);
    digitalWrite(SENSOR_1_PIN, LOW);
    digitalWrite(SENSOR_2_PIN, LOW);
    digitalWrite(SENSOR_3_PIN, LOW);

    delay(5);
    sensor1.setBus(&Wire1);
    sensor2.setBus(&Wire1);
    sensor3.setBus(&Wire1);
    pinMode(SENSOR_1_PIN, INPUT);
    delay(15);
    Serial.println("00");
    sensor1.init(true);
    Serial.println("01");
    delay(10);
    sensor1.setAddress((uint8_t)22);
    Serial.println("02");

    //SENSOR 2
    pinMode(SENSOR_2_PIN, INPUT);
    delay(15);
    sensor2.init(true);
    Serial.println("03");
    delay(10);
    sensor2.setAddress((uint8_t)25);
    Serial.println("04");

    //SENSOR 3
    pinMode(SENSOR_3_PIN, INPUT);
    delay(15);
    sensor3.init(true);
    Serial.println("05");
    delay(10);
    sensor3.setAddress((uint8_t)28);
    Serial.println("06");

    Serial.println("");
    Serial.println("addresses set");
    Serial.println("");
    Serial.println("");

    sensor1.setTimeout(50);
    sensor2.setTimeout(50);
    sensor3.setTimeout(50);
}

void RTPThreeAxisVL::startContinuous(){
    sensor1.startContinuous();
    sensor2.startContinuous();
    sensor3.startContinuous();
}

void RTPThreeAxisVL::stopContinuous(){
    sensor1.stopContinuous();
    sensor2.stopContinuous();
    sensor3.stopContinuous();
}

void RTPThreeAxisVL::setMaxLimitReading(int maxReading){
    _maxLimitReading = maxReading;
}

int RTPThreeAxisVL::getMaxLimitReading(){
    return _maxLimitReading;
}

void RTPThreeAxisVL::setMinLimitReading(int minReading){
    _minLimitReading = minReading;
}

int RTPThreeAxisVL::getMinLimitReading(){
    return _minLimitReading;
}

ThreeReadings RTPThreeAxisVL::getThreeReadings(){
    ThreeReadings readings;
    readings.sensorReading1 = sensor1.readRangeContinuousMillimeters();
    readings.sensorReading2 = sensor2.readRangeContinuousMillimeters();
    readings.sensorReading3 = sensor3.readRangeContinuousMillimeters();
    return readings;
}

ThreeReadings RTPThreeAxisVL::getThreeCleanReadings(){
    ThreeReadings readings = getThreeReadings();
    readings.sensorReading1 = readings.sensorReading1 > _maxLimitReading ? -1 : readings.sensorReading1;
    readings.sensorReading1 = constrain(readings.sensorReading1, -1, _maxLimitReading);
    readings.sensorReading2 = readings.sensorReading2 > _maxLimitReading ? -1 : readings.sensorReading2;
    readings.sensorReading2 = constrain(readings.sensorReading2, -1, _maxLimitReading);
    readings.sensorReading3 = readings.sensorReading3 > _maxLimitReading ? -1 : readings.sensorReading3;
    readings.sensorReading3 = constrain(readings.sensorReading3, -1, _maxLimitReading);
    return readings;
}

void RTPThreeAxisVL::callbackThreeAxisChanged(void (*userFunc) (ControlCommand callbackCommand)){
    ThreeReadings readings = getThreeCleanReadings();
    if(readings.sensorReading1 != lastReadings.sensorReading1 && readings.sensorReading1 != -1){
        ControlCommand command;
        command.controlType = SENSOR_1_ID;
        command.commandType = CONTROL_ID;
        command.value = readings.sensorReading1;
        userFunc(command);
    }
    if(readings.sensorReading2 != lastReadings.sensorReading2 && readings.sensorReading2 != -1){
        ControlCommand command;
        command.controlType = SENSOR_2_ID;
        command.commandType = CONTROL_ID;
        command.value = readings.sensorReading2;
        userFunc(command);
    }
    if(readings.sensorReading3 != lastReadings.sensorReading3 && readings.sensorReading3 != -1){
        ControlCommand command;
        command.controlType = SENSOR_3_ID;
        command.commandType = CONTROL_ID;
        command.value = readings.sensorReading3;
        userFunc(command);
    }
    lastReadings = readings;
}


