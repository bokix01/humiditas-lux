# Humiditas Lux
Innovative system for illumination of road marks when humidity is high (usually when it's raining or there is fog) in combination with darkness at night.

## Components

### Road model / mockup
- Dasduino CONNECTPLUS (ESP32)
- DHT11 (Temperature and humidity sensor)
- Photoresistor
- 10K ohm resistor
- LEDs (Red, yellow & white)

### Station (Wi-Fi Server)
- Arduino MKR1000
- DHT11 (Temperature and humidity sensor)
- Photoresistor
- 10K ohm resistor

### Light (Wi-Fi Client)
- Arduino MKR1000
- WS2812 5x5 LED matrix

## Settings
You can adjust the maximum allowed light and humidity values in these variables
```
const int max_allowed_light = 1900;	  // 1900 and below is night
const int max_allowed_humidity = 75;	// 75% and above is rain/fog
```

You can adjust the Wi-Fi and server settings in these variables
```
const char* SSID = "";			  // Put your Wi-Fi SSID here
const char* PASSWORD = "";		// Put your Wi-Fi password here
const int SERVER_PORT = 80;		// Port your server will run on
```
