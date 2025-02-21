// Author: BuffBaby253
// Description: WiFi Displayed Tempeterature & Humidity Sensor 
// Libraries Needed: DHT Sensor Library by Adafruit, LiquidCrystal I2C by Frank de Barbander & WiFiS3 from Arduino Uno R4 Wifi board library

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <WiFiS3.h> // For Uno R4 WiFi

#define DHTPIN 2
#define DHTTYPE DHT22 // Change to your sensor module if needed

LiquidCrystal_I2C lcd(0x27, 20, 4); // Adjust I2C address and LCD size if needed
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WiFiServer server(80); // Create a server on port 80

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  lcd.init();
  lcd.backlight();

  // Connect to Wi-Fi
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true); // Halt if the Wi-Fi module is not found
  }

  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  delay(2000);

  float h, t, f, hic, hif;
  if (readSensorData(h, t, f, hic, hif)) {
    displaySensorData(h, t, f);
  } else {
    Serial.println(F("Failed to read from DHT sensor!"));
  }

  
  WiFiClient client = server.available();
  if (client) {
    handleClientRequest(client);
    client.stop();
  }
}

bool readSensorData(float &h, float &t, float &f, float &hic, float &hif) {
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    return false;
  }

  hif = dht.computeHeatIndex(f, h);
  hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  return true;
}

void displaySensorData(float h, float t, float f) {
  lcd.setCursor(0, 0);
  lcd.print(" Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print(" Temp: ");
  lcd.print(f);
  lcd.print("F");
}

void handleClientRequest(WiFiClient &client) {
  if (client.connected()) {
    // Read the request
    String request = client.readStringUntil('\r');
    Serial.println(request); // Print the request for debugging
    client.flush();

    // Prepare the response
    float h, t, f, hic, hif;
    if (readSensorData(h, t, f, hic, hif)) {
      String html = "<html><body><h1>Sensor Data</h1>";
      html += "<p>Humidity: " + String(h) + "%</p>";
      html += "<p>Temperature: " + String(t) + "°C / " + String(f) + "°F</p>";
      html += "<p>Heat Index: " + String(hic) + "°C / " + String(hif) + "°F</p>";
      html += "</body></html>";

      // Send the HTTP response
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();
      client.println(html);
    } else {
      client.println("HTTP/1.1 500 Internal Server Error");
      client.println("Content-Type: text/plain");
      client.println("Connection: close");
      client.println();
      client.println("Failed to read sensor data");
    }
  }
}
