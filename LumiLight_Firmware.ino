#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <LittleFS.h>

#define LDR D2
#define LED D1
#define SERIAL_BAUD 115200
#define WIFI_DELAY 500
#define MAX_SSID_LEN 32
#define MAX_CONNECT_TIME 30000
#define REFRESH 30000

char ssid[MAX_SSID_LEN] = "";
int sensorValue;
int Prev_sensorValue;
String API_URL = "http://lumi-light-api.herokuapp.com";

//--------------------------------------encode--------------------------------------------------------------

bool encode(int state) {
  if (state == 0) {
    return true;
  }
  if (state == 1) {
    return false;
  }
}


void loop() {
  //pass
}
