#include <Arduino.h> // Include Arduino.h if you are using VSC instead of Arduino IDE
#include <MQUnifiedsensor.h>

#define RATIO_MQ2_CLEAN_AIR 9.83

class MQ2 {
    public:
        MQ2(String board, String type, float voltage = 5, int pin = A0) 
            : _sensor(board, voltage, 10, pin, type), _pin(pin) {
                _sensor.setRegressionMethod(1);
                _sensor.setA(3616.1);
                _sensor.setB(-2.68);
                _sensor.init();

                /*
                    Exponential regression:
                    Gas    | a      | b
                    H2     | 987.99 | -2.162
                    LPG    | 574.25 | -2.222
                    CO     | 36974  | -3.109
                    Alcohol| 3616.1 | -2.675
                    Propane| 658.71 | -2.168
                */

                
                _sensor.serialDebug(true);
            };
        
        void update();
        void serialDebug();
        float calibrate(int calibrateRounds = 10);
        float readPPM();

    private:
        MQUnifiedsensor _sensor;
        int _pin;
};

/*
    MQ2UnifiedSensor Library under the hood: https://github.com/miguel5612/MQSensorsLib/tree/master/src
    Example: https://github.com/miguel5612/MQSensorsLib/blob/master/examples/MQ-2/MQ-2.ino
*/