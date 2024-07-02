#include "sht.h"

void SHT::read() {
    this->_sht.read();
}

void SHT::switchHeater(bool onOff) {
    // Switch the heater on an off
    onOff && heaterIsReady() ? this->_sht.heatOn() : this->_sht.heatOff();
    
    if (onOff)
        this->lastHeatMillis = millis();
}

bool SHT::heaterIsReady() {
    // Multiply SHT_HEAT_TIMEOUT with 1000 to get to milliseconds.
    return millis() - this->lastHeatMillis > SHT_HEAT_TIMEOUT * 1000;
}


float SHT::getHumidity() {
    return this->_sht.getHumidity();
    // return !this->_sht.isHeaterOn() ? 0 : this->_sht.getHumidity();
}

float SHT::getTemperature() {
    return this->_sht.getTemperature();
    // return !this->_sht.isHeaterOn() ? 0 : this->_sht.getTemperature();
}