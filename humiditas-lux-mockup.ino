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

#include <DHT11.h>

#define PHOTORESISTOR_PIN 15
#define DHT11_PIN 14
#define LED_PIN1 13
#define LED_PIN2 12

DHT11 dht11(DHT11_PIN);

int light;
int humidity;
bool criteriaMet = false;

int max_allowed_light = 1900;  // 1900 and below is night
int max_allowed_humidity = 75;  // 75 and above is rain/fog
/*
THESE SETTINGS ARE FOR TEST/DISPLAY VERSION ONLY!!!
REAL WORLD VALUES MAY DIFFER!!!
CHANGE THEM ACCORDINGLY!!!
*/

void setup() {
  Serial.begin(9600);

  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void loop() {
  light = analogRead(PHOTORESISTOR_PIN);
  Serial.print("Light: ");
  Serial.print(light);
  Serial.print(" / ");
  Serial.println(max_allowed_light);

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

  if (light <= max_allowed_light && humidity >= max_allowed_humidity) {
    Serial.println("All criteria are met. Turning on the LEDs...");
    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    criteriaMet = true;
  } else if (criteriaMet) {
    Serial.println("All criteria are no longer met. Turning off the LEDs...");
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    criteriaMet = false;
  }
}
