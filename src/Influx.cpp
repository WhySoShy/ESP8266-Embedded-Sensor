#include "Influx.h"
#define WIFI_TIMEOUT 5000

// You can add multiple ones and the WIFI Module will select the strongest one.
void Influx::addWifi(char* ssid, char* password) {
    this->_wifi.addAP(ssid, password);
    Serial.print("Wifi "); Serial.print(ssid); Serial.println(" Added");
}

// Ensure that the time is set, if not the timestamp saved will be wrong.
void Influx::setTime(char* timeZone) {
    timeSync(timeZone, "dk.pool.ntp.org", "pool.ntp.org");
    Serial.print("Set time zone to "); Serial.println(timeZone);
}

void Influx::addField(String field, float data) {
    this->_point.addField(field, data);
}

// Tags are "static" fields, that can be used to identify a device for example.
void Influx::addTag(String tag, String data) {
    this->_point.addTag(tag, data);
    Serial.print("Added tag"); Serial.println(tag);
}

void Influx::clearFields() {
    this->_point.clearFields();
}

void Influx::saveData() {
    this->_client.writePoint(this->_point);
}

void Influx::ensureInternetConnection(bool isSetup) {
    bool lostConnection = false;
    // Hvis du allerede er tilsluttet internettet, kommer den ikke ind i while loopet.
    if (this->_wifi.run(WIFI_TIMEOUT) != WL_CONNECTED) {
        Serial.print(isSetup ? "Connecting to wifi" : "Trying to reconnect to wifi");
        lostConnection = true;
    }

    while (this->_wifi.run(WIFI_TIMEOUT) != WL_CONNECTED) {
        Serial.print(".");
        delay(1);
    }
    // Udskriv kun hvis du har haft mistet internettet
    if (lostConnection || isSetup) Serial.println("Connected to WIFI");
    Serial.println("Ensured internet connection");
}

bool Influx::isConnectedToInflux() {
    return _client.validateConnection();
}