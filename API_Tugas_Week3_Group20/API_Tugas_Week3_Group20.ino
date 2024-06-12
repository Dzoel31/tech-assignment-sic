#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"
#define MQ_PIN 34

const char* ssid = "FIK-Hotspot";
const char* password = "FIK22-23!";
const char* serverName = "http://172.23.22.75:8000/create";

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


// #define DHTPIN 4       // GPIO pin where the DHT11 data pin is connected
// #define DHTTYPE DHT11  // DHT 11


// void setup() {
//   Serial.begin(115200);
  // dht.begin();
// }

// void loop() {
//   delay(2000);  // Wait a few seconds between measurements

//   // Reading temperature or humidity takes about 250 milliseconds!
//   // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//   float humidity = dht.readHumidity();
//   float temperature = dht.readTemperature();
//   Serial.println("Trying to read from DHT sensor!");

//   // Check if any reads failed and exit early (to try again).
  // if (isnan(humidity) || isnan(temperature)) {
  //   Serial.println("Failed to read from DHT sensor!");
  //   return;
  // }

//   // Print the results to the Serial Monitor
//   Serial.print("Humidity: ");
//   Serial.print(humidity);
//   Serial.println(" %\t");
//   Serial.print("Temperature: ");
//   Serial.print(temperature);
//   Serial.println(" °C");
// }

// #define MQ_PIN 34  // GPIO pin where the MQ sensor AO is connected

// void setup() {
//   Serial.begin(115200);
//   pinMode(MQ_PIN, INPUT);  // Set the analog pin as input
// }

// void loop() {
//   int sensorValue = analogRead(MQ_PIN);  // Read the analog value from the sensor
//   Serial.print("MQ Sensor Value: ");
//   Serial.println(sensorValue);
//   delay(4000);  // Wait for a second before reading again
// }

// #include "DHT.h"

// // Definisikan pin dan tipe sensor
// #define DHTPIN 4     // Pin yang terhubung ke pin data DHT11
// #define DHTTYPE DHT22   // DHT 11

// // Inisialisasi DHT sensor
// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(115200);
//   Serial.println("DHT11 sensor initialization");

//   dht.begin();
// }

// void loop() {
//   // Tunggu beberapa saat agar pembacaan stabil
//   delay(2000);

//   // Baca kelembaban
//   float humidity = dht.readHumidity();
//   // Baca suhu dalam Celcius
//   float temperature = dht.readTemperature();
  
//   // Cek apakah pembacaan berhasil
//   if (isnan(humidity) || isnan(temperature)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }

//   // Tampilkan hasil
//   Serial.print("Humidity: ");
//   Serial.print(humidity);
//   Serial.print(" %\t");
//   Serial.print("Temperature: ");
//   Serial.print(temperature);
//   Serial.println(" *C");
// }

