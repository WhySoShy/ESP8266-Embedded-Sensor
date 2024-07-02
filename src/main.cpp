#include <Arduino.h> // Include Arduino.h if you are using VSC instead of Arduino IDE
#include "Influx.h"
#include "mq2.h"
#include "sht.h"
#include "arduino_secrets.h"
#define RUN_TIME 10 // RUN_TIME is in seconds.


Influx influx(INFLUXDB_URL, INFLUXDB_TOKEN, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_MEASUREMENT);

MQ2 mq2("ESP8266 Dev", "MQ2", 5, A0);

SHT sht;

void runSht();
void runMQ2();

void setup() {
    if (!Serial)
        Serial.begin(9600);

    delay(5);
    // You can add more than 1 wifi and it will select the strongest one to use.

    influx.ensureInternetConnection(true);

    influx.setTime(TZ_INFO);
    influx.addTag("Device", "ESP8266");

    // If we are not connected to influxDB, just run a loop until it is connected.
    bool first = false;
    while (!influx.isConnectedToInflux()) {
        if (!first) {
            Serial.print("Cannot connect to influx");
            first = true;
        }

        Serial.print(".");
    }
    Serial.println();

    mq2.calibrate();
}

unsigned long runData = RUN_TIME * 1000;

void loop() {
    if (millis() - runData < RUN_TIME * 1000)
        return;

    influx.clearFields();
    runData = millis();

    // Ensure that a backup network takes over if connection is lost.
    influx.ensureInternetConnection(false);
    runSht();
    runMQ2();
    delay(25);
    // Serial.println("Saved");
    influx.saveData();
}

void runSht () {
    sht.switchHeater(true);

    sht.read();
    influx.addField("Tempature", sht.getTemperature());
    influx.addField("Humidity", sht.getHumidity());

    sht.switchHeater(false);
}

void runMQ2() {
    // Get the newest results from our Gas sensor
    mq2.update();
    influx.addField("PPM", mq2.readPPM());
}