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

//---------------------------------------AUTO_WIFI----------------------------------------------------------

void scanAndSort() {
  memset(ssid, 0, MAX_SSID_LEN);
  int n = WiFi.scanNetworks();
  if (n != 0) {
    int indices[n];
    for (int i = 0; i < n; i++) {
      indices[i] = i;
    }
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
          std::swap(indices[i], indices[j]);
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      if (WiFi.encryptionType(indices[i]) == ENC_TYPE_NONE) {
        memset(ssid, 0, MAX_SSID_LEN);
        strncpy(ssid, WiFi.SSID(indices[i]).c_str(), MAX_SSID_LEN);
        break;
      }
    }
  }
}

void Connect() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(WIFI_DELAY);
    scanAndSort();
    delay(WIFI_DELAY);
    if (strlen(ssid) > 0) {
      WiFi.begin(ssid);
      unsigned short try_cnt = 0;
      while (WiFi.status() != WL_CONNECTED && try_cnt < MAX_CONNECT_TIME / WIFI_DELAY) {
        delay(WIFI_DELAY);
        Serial.print(".");
        try_cnt++;
      }
    }
  }
}

void WIFI() {
  Connect();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("\n Trying to Connect with nearby networks........ \n");
    delay(REFRESH);
    Connect();
  }
}

//---------------------------------------------------HTTP_REQUEST-----------------------------------------------

String Get_Init() {
  WiFiClient client;
  HTTPClient http;
  String URL = API_URL + "/init";
  http.begin(client, URL);
  int httpResponseCode = http.GET();
  if (httpResponseCode == 201) {
    String payload = http.getString();
    return payload;
  } else {
    ESP.restart();
  }
}

bool Post_Update(String ID, bool State, String Loc) {
  WiFiClient client;
  HTTPClient http;
  String URL = API_URL + "/update";
  http.begin(client, URL);
  http.addHeader("Content-Type", "application/json");
  String Json = "{";
  Json = Json + " \"ID\" : " + ID + " , ";
  if (State) {
    Json = Json + " \"Status\" : true  , ";
  } else {
    Json = Json + " \"Status\" : false , ";
  }
  Json = Json + " \"Loc\" : " + Loc;
  Json = Json + "}";
  Serial.print("\n" + Json + "\n");
  int httpResponseCode = http.POST(Json);
  if (httpResponseCode == 201) {
    return true;
  } else {
    return false;
  }
}




void loop() {
  //pass
}
