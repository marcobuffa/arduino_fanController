#include <Arduino.h>
#include "DHT.h"

#define DHT11_PIN 2
#define MAINCYCLE 5000ul

#define SERIALDEBUG

static const int DHT_SENSOR_PIN = 2;
static unsigned long now = 0;
static unsigned long counting = 0;
float temperature = 20;
float humidity = 50;
DHT dht11(DHT11_PIN, DHT11);

void setup() {
    Serial.begin(115200);
    dht11.begin();
}

void measureRoom(float *temperature, float *humidity){
#ifdef SERIALDEBUG
  Serial.print("measureRoom IN: ");
  Serial.println(millis());
#endif
  *humidity = dht11.readHumidity();
  *temperature = dht11.readTemperature();
#ifdef SERIALDEBUG
  Serial.print("measureRoom OUT: ");
  Serial.println(millis());
#endif
  return;
}

void loop() {
  now = millis();

  if (now - counting >= MAINCYCLE){
    counting = now;
    Serial.print(now);
    measureRoom(&temperature, &humidity);
    Serial.print(": T = ");
    Serial.print(temperature, 2);
    Serial.print("°C | RH = ");
    Serial.print(humidity, 2);
    Serial.println("%");
  }
}