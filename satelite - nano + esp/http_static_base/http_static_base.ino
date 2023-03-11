#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "DIGIFIBRA-y54u";
const char* password = "zKxYbSfcEF";
const char* host = "192.168.1.133:3000";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
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
