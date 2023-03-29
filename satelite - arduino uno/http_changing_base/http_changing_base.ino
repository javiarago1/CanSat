#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SerialTransfer.h>

const char* ssid = "DIGIFIBRA-y54u";
const char* password = "zKxYbSfcEF";
const char* host = "192.168.1.133:3000";

SerialTransfer serialTransfer;

struct PressureInfo {
  float pressure;
};

struct PressureInfo pressureInfo;

void setup() {
  Serial.begin(9600);
  serialTransfer.begin(Serial);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  getPressureAndSendToUNO();
}

void getPressureAndSendToUNO() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    http.begin(client, "http://" + String(host) + "/api/pressure");
    int httpCode = http.GET();

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error) {
          unsigned long startTime = millis();
          bool pressureReceived = false;
          float pressure = doc["pressure"];
          pressureInfo.pressure = pressure;
          while (!pressureReceived && millis() - startTime < 20000) {
            uint16_t sendSize = 0;
            sendSize = serialTransfer.txObj(pressureInfo, sendSize);
            serialTransfer.sendData(sendSize);
            delay(500);
            if (serialTransfer.available()) {
              pressureReceived = true;
            }
          }
        } else {
          Serial.println("Error al deserializar el JSON");
        }
      }
    } else {
      Serial.println("Error en la solicitud HTTP");
    }

    http.end();
  }
}

void sendDataToServer(String json) {
  bool sent = false;
  int retries = 0;
  while (!sent && retries < 5) {
    HTTPClient http;
    WiFiClient client;
    http.begin(client, "http://" + String(host) + "/api/insertData");
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(json);
    if (httpResponseCode > 0) {
      sent = true;
    } else {
      Serial.println("Error sending POST request, retrying...");
      retries++;
    }
    http.end();
  }
}


String buffer = "";
int first = -1;
void loop() {

  while (Serial.available()) {
    char c = Serial.read();
    buffer += c;
    if (c == '{') {
      first = buffer.length() - 1;
    } else if (c == '}') {
      if (first != -1) {

        String finalString = buffer.substring(first, buffer.length());
        Serial.println(finalString);
        sendDataToServer(finalString);
      }
      first = -1;
      buffer = "";
    }
  }
}
