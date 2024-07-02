#include <Arduino.h> // Include Arduino.h if you are using VSC instead of Arduino IDE
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <ESP8266WiFiMulti.h>

#define FAILED_TRIES 7
#define WIFI_MODE WIFI_STA

class Influx {
    public:        
        void addWifi(char* ssid, char* password);
        
        void setTime(char* timeZone);
        void addField(String field, float data);
        void addTag(String tag, String data);
        void clearFields();
        void saveData();
        void ensureInternetConnection(bool isSetup);
        bool isConnectedToInflux();

        Influx(String url, String token, String org, String bucket, String measurement) 
        : _client(url, org, bucket, token, InfluxDbCloud2CACert), _point(measurement) {
            WiFi.mode(WIFI_MODE);

            Serial.println("InfluxDB Setup done");
        };

    private:
        Point _point;
        ESP8266WiFiMulti _wifi;
        InfluxDBClient _client; // Setup by constructor
};