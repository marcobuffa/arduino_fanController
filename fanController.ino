#include <Arduino.h>
#include "DHT.h"

#define DHT11_PIN 2
#define MAINCYCLE 5000ul

#undef SERIALDEBUG

static const int DHT_SENSOR_PIN = 2;
static unsigned long now = 0;
static unsigned long counting = 0;
float temperature = 20;
float humidity = 50;
float dewPoint = 0;

DHT dht11(DHT11_PIN, DHT11);

// DHT11 measurement routine
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


//Dew Point calculation routine
float findDewPoint(float t, float rh){
    return (t - (14.55 + 0.114 * t) * (1 - (0.01 * rh)) - pow(((2.5 + 0.007 * t) * (1 - (0.01 * rh))),3) - (15.9 + 0.117 * t) * pow((1 - (0.01 * rh)), 14));
}


//Arduino setup routine
void setup() {
    Serial.begin(115200);
    dht11.begin();
}


//Arduino cyclic routine
void loop() {
  now = millis();

  if (now - counting >= MAINCYCLE){
    counting = now;
    Serial.print(now);
    measureRoom(&temperature, &humidity);
    dewPoint = findDewPoint(temperature, humidity);
    Serial.print(": T = ");
    Serial.print(temperature, 2);
    Serial.print("°C | RH = ");
    Serial.print(humidity, 2);
    Serial.print("% | Dew = ");
    Serial.print(dewPoint, 2);
    Serial.println("°C");
  }
}