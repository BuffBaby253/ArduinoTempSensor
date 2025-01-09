// Author: BuffBaby253
// Libraries Needed: DHT Sensor Library by Adafruit & LiquidCrystal I2C by Frank de Barbander

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22 // Change to your sensor module if needed

LiquidCrystal_I2C lcd(0x27,20,4);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  lcd.begin(16, 2);



}


void loop()
{
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

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

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);


  lcd.print(" Humidity: ");
  lcd.print(h);

  lcd.setCursor(2, 1);
  lcd.print(" Temp: ");
  lcd.print(f);
}
