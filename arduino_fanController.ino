//Using https://github.com/adafruit/DHT-sensor-library
#include "DHT.h"

#define FAN 2
#define DHTPIN 4
#define DHTTYPE DHT11
#define BAUDRATE 115200

static unsigned int currentTime = 0;
static unsigned int time;

float dewPoint(float h, float t) {
    return (t - (14.55 + 0.114 * t) * (1 - (0.01 * h)) - pow(((2.5 + 0.007 * t) * (1 - (0.01 * h))),3) - (15.9 + 0.117 * t) * pow((1 - (0.01 * h)), 14));
}

DHT dht(DHTPIN, DHTTYPE); //sensor

void setup() {
  pinMode(FAN, OUTPUT); //initialize fan control pin
  Serial.begin(BAUDRATE); //initialize serial port

  dht.begin(); //start sensor library
}

void loop() {
  float h, t, dp;

  time = millis();
  if ((time - currentTime) >= 3000){
    currentTime = time;

    Serial.print(time);

    //read sensor
    h = dht.readHumidity();
    t = dht.readTemperature();
    dp = dewPoint(h, t);

    Serial.print(" | RH%: ");
    Serial.print(h);
    Serial.print(" | T°C: ");
    Serial.print(t);
    Serial.print(" | DP°C: ");
    Serial.print(dp);

    if (digitalRead(FAN) == HIGH){
      digitalWrite(FAN, LOW);
      Serial.println(" | OFF");
    } else {
      digitalWrite(FAN, HIGH);
      Serial.println(" | ON");
    }
  }
}
