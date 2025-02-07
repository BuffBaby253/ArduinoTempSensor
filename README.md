# Arduino Temperature & Humidity Sensor

![20250107_112843](https://github.com/user-attachments/assets/5f1872fa-e76f-4267-a386-70b559a2e95f)


## Uses a liquid crystal display to display temperature and humidity from a DHT22 sensor that updates every 2 seconds
> [!NOTE]
> DHT21 & DHT11 works with this project too

# Hardware Needed
- Arduino Uno
- Liquid Crystal Display (With I2C Module)
- DHT22/AM2302

# Wiring
### No Breadboard Needed

DHT22 | Arduino
----    |   ----
GND |   GND
VCC |   3.3V
DAT |   2

LCD |   Arduino
----    |   ----
GND |   GND
VCC |   5V
SDA |   A4
SCL |   A5

# TODO
- Configure with Wi-Fi
