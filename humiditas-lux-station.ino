/*

Humiditas Lux

Copyright 2024 Borna Krpan

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#include <SPI.h>
#include <WiFi101.h>
#include <DHT11.h>

// Wi-Fi Connection
const char* SSID = "";                      // Wi-Fi SSID
const char* PASSWORD = "";                  // Wi-Fi Password
const int SERVER_PORT = 80;                 // Server hosting port

WiFiServer server(SERVER_PORT);

// Components
const int PHOTORESISTOR_PIN 2;
const int DHT11_PIN 5;

DHT11 dht11(DHT11_PIN);

int light;
int humidity;
bool criteriaMet = false;

const int max_allowed_light = 1900;         // 1900 and below is night
const int max_allowed_humidity = 75;        // 75 and above is rain/fog
/*
THESE SETTINGS ARE FOR TEST/DISPLAY VERSION ONLY!!!
REAL WORLD VALUES MAY DIFFER!!!
CHANGE THEM ACCORDINGLY!!!
*/

void setup() {
  Serial.begin(9600);

  pinMode(PHOTORESISTOR_PIN, INPUT);
  
  // Attempt to connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(SSID);
  while (WiFi.begin(SSID, PASSWORD) != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Successful connection
  Serial.println("Connected to WiFi");
  Serial.print("Server (current device) IP Address: ");

  // Print the IP address in standard dotted notation
  int ip = WiFi.localIP();
  Serial.print(ip & 0xFF);
  Serial.print(".");
  Serial.print((ip >> 8) & 0xFF);
  Serial.print(".");
  Serial.print((ip >> 16) & 0xFF);
  Serial.print(".");
  Serial.println((ip >> 24) & 0xFF);

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();    // Check if a client is connected
  
  if (client) {
    Serial.println("Client connected");
    
    while (client.connected()) {
      // Light reading
      light = analogRead(PHOTORESISTOR_PIN);
      Serial.print("Light: ");
      Serial.print(light);
      Serial.print(" / ");
      Serial.println(max_allowed_light);

      // Humidity reading
      humidity = dht11.readHumidity();
      if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
          Serial.print("Humidity: ");
          Serial.print(humidity);
          Serial.print("% / ");
          Serial.print(max_allowed_humidity);
          Serial.println("%");
      } else {
          Serial.println(DHT11::getErrorString(humidity));
      }

      // Check for night and rain
      if (light <= max_allowed_light && humidity >= max_allowed_humidity && !criteriaMet) {
        Serial.println("All criteria are met. Turning on the LEDs...");
        client.println("on");
        Serial.println("Message sent to client.");
        criteriaMet = true;
      } else if (criteriaMet) {
        Serial.println("All criteria are no longer met. Turning off the LEDs...");
        client.println("off");
        Serial.println("Message sent to client.");
        criteriaMet = false;
      }

      delay(50);
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
