#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#define MQ_PIN 34

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
const char* serverName = "http://<ipv4 address>:8000/create";

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(MQ_PIN, INPUT);
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);  // Specify the URL

    int sensorValue = analogRead(MQ_PIN);  // Read the analog value from the sensor
    Serial.print("MQ Sensor Value: ");
    Serial.println(sensorValue);

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");

    // Create JSON object
    StaticJsonDocument<200> doc;
    doc["name"] = "ESP32";
    doc["value"] = sensorValue;

    String requestBody;
    serializeJson(doc, requestBody);

    // Send HTTP POST request
    int httpResponseCode = http.POST(requestBody);
    
    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response to the request
      Serial.println(httpResponseCode);    // Print return code
      Serial.println(response);            // Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Free resources
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(5000);

}