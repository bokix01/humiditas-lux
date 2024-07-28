# Humiditas Lux
Innovative system for illumination of road marks when humidity is high (usually when it's raining or there is fog) in combination with dark at night.

## Components
- Dasduino CONNECTPLUS (ESP32)
- DHT11 (Temperature and humidity sensor)
- Photoresistor
- LEDs (Red, yellow & white)

## Settings
You can adjust the maximum allowed light and humidity values in these variables
```
int max_allowed_light = 1900;  // 1900 and below is night
int max_allowed_humidity = 75;  // 75% and above is rain/fog
```
