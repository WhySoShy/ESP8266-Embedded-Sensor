#include "mq2.h"

void MQ2::update() {
    this->_sensor.update();
}

void MQ2::serialDebug() {
    this->_sensor.serialDebug();
}

// Calibration number is being used to calculate the PPM of the gas.
float MQ2::calibrate(int calibrateRounds) {
    Serial.println("Calibrating");
    float calibrateResult = 0;
    for(int i = 1; i <= calibrateRounds; i++, 
            this->_sensor.update(),
            calibrateResult += this->_sensor.calibrate(RATIO_MQ2_CLEAN_AIR)
        );

    this->_sensor.setR0(calibrateResult/10);
    Serial.println("Calibration done");

    return calibrateResult;
}

float MQ2::readPPM() {
    return this->_sensor.readSensor();
}
