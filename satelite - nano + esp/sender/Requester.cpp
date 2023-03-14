#include "Requester.h"

Requester::Requester()
  : serialPort(2) {
  Serial.begin(9600);
  serialPort.begin(9600, SERIAL_8N1, rx2pin, tx2pin);
  serialTransfer.begin(serialPort);
}

char rec[3];

void Requester::sendPressureToNano(float dailiyPressure) {
  Serial.println("WAT?");
  unsigned long startTime = millis();
  bool received = false;
  ConfigData configData;
  configData.pressure = dailiyPressure;
  uint16_t sendSize = 0;
  while (millis() - startTime < 20000 && !received) {
    sendSize = serialTransfer.txObj(configData, sendSize);
    serialTransfer.sendData(sendSize);
    delay(1000);
    if (serialTransfer.available()) {
      uint16_t recSize = 0;
      recSize = serialTransfer.rxObj(rec, recSize);
      if (strcmp(rec, "REC") == 0) {
        Serial.println("Configuration of pressure correctly");
        received = true;
      } else {
        Serial.println("Not receiving response of configuration success");
      }
    }
  }
}

void Requester::setupWifi(const char* ssid, const char* password) {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - startTime >= 10000) {
      Serial.println("\nFailed to connect to WiFi after 10 seconds.");
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  }
}

void Requester::requestMadridDailyPressure(TPAManager& tpaManager) {
  Serial.begin(9600);
  //Your Domain name with URL path or IP address with path
  String serverPath = "http://192.168.1.133:3000/api/pressure";

  //Send an HTTP POST request every 10 minutes
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(serverPath.c_str());

    // If you need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      StaticJsonDocument<48> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }
      float pressure = doc["pressure"];
      tpaManager.dailyPressure = pressure;


    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}
