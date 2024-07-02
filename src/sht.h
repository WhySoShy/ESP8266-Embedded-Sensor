#include <Arduino.h> // Include Arduino.h if you are using VSC instead of Arduino IDE
#include <SHT31.h>
#include <Wire.h>

#define SHT31_ADDRESS 0x44
// Is written in seconds, and the heater is getting automatically turned off after 10 seconds.
#define SHT_HEAT_TIMEOUT 10

class SHT {
    public:
        unsigned long lastHeatMillis = 0;

        void read();
        void switchHeater(bool onOff);
        bool heaterIsReady();
        float getHumidity();
        float getTemperature();

        SHT() : _sht(SHT31_ADDRESS) {
            Wire.begin();
            _sht.begin();
            _sht.setHeatTimeout(SHT_HEAT_TIMEOUT);

            Serial.println("SHT Setup done");
        };

    private:
        SHT31 _sht;
};