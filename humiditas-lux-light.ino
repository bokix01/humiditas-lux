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
#include <Adafruit_NeoPixel.h>

// Wi-Fi Connection
const char* SSID = "";                        // Wi-Fi SSID
const char* PASSWORD = "";                    // Wi-Fi Password
const char* SERVER_IP = "192.168.X.X";        // Server IP address
const int SERVER_PORT = 80;                   // Server hosting port

WiFiClient client;

// Components
#define NUM_LEDS 25
#define LED_PIN 5

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void connect() {
  // Attempt to connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(SSID);
  while (WiFi.begin(SSID, PASSWORD) != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Successful connection
  Serial.println("Connected to WiFi");
  Serial.print("Client (current device) IP Address: ");

  // Print the IP address in standard dotted notation
  int ip = WiFi.localIP();
  Serial.print(ip & 0xFF);
  Serial.print(".");
  Serial.print((ip >> 8) & 0xFF);
  Serial.print(".");
  Serial.print((ip >> 16) & 0xFF);
  Serial.print(".");
  Serial.println((ip >> 24) & 0xFF);

  // Attempt to connect to the server
  if (client.connect(SERVER_IP, SERVER_PORT)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection to server failed");
  }
}

void setup() {
  Serial.begin(115200);

  matrix.begin();
  matrix.show();
  
  connect();
}

void loop() {
  if (client.connected()) {
    while (client.available()) {
      String message = client.readStringUntil('\n');
      Serial.print("Message received: ");
      Serial.print("\"");
      Serial.print(message);
      Serial.println("\"");
      message.trim();

      // Check for message content
      if (message == "on") {
        for (int i = 0; i < NUM_LEDS; i++) {
          matrix.setPixelColor(i, matrix.Color(127, 127, 127));
        }
        matrix.show();
        Serial.println("Action: Turning ON");
      } else if (message == "off") {
        for (int i = 0; i < NUM_LEDS; i++) {
          matrix.setPixelColor(i, matrix.Color(0, 0, 0));
        }
        matrix.show();
        Serial.println("Action: Turning OFF");
      }
    }
  } else {
    Serial.println("Disconnected from server, trying again...");
    delay(500);
    connect();
  }
}
