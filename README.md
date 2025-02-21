# Arduino Uno R4 Temperature & Humidity Sensor

![20250107_112843](https://github.com/user-attachments/assets/5f1872fa-e76f-4267-a386-70b559a2e95f)


## Uses a liquid crystal display to display temperature and humidity from a DHT22 sensor that updates every 2 seconds
### Added ability to connect to WiFi to display data with added Heat Index & both Farenheit and Celcius

![Image](https://github.com/user-attachments/assets/d46d2cbe-f724-4ae4-8c63-7586d32939ac)
I know not so pretty but for demonstration

> [!NOTE]
> DHT21 & DHT11 works with this project too
> Change in lines 16 & 17 to your WiFi name and password

After uploading the code to the Arduino, go to the serial monitor, as it connects to your WiFi it will display it has connected and the IP address to go to. It will then log all the info displayed from the sensor to the web server.

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


