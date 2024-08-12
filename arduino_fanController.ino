#include "hardware.h"
#include "software.h"

static unsigned int currentTime = 0;
static unsigned int time;

float dewPoint(float h, float t) {
    return (t - (14.55 + 0.114 * t) * (1 - (0.01 * h)) - pow(((2.5 + 0.007 * t) * (1 - (0.01 * h))),3) - (15.9 + 0.117 * t) * pow((1 - (0.01 * h)), 14));
}

DHT dht(DHTPIN, DHTTYPE); //sensor

void setup() {
  pinMode(FAN, OUTPUT); //initialize fan control pin

#ifdef DEBUG
  Serial.begin(BAUDRATE); //initialize serial port
#endif

  dht.begin(); //start sensor library
}

void loop() {
  float h, t, dp;

  time = millis();
  if ((time - currentTime) >= 3000){

    //save time
    currentTime = time;

    //read sensor
    h = dht.readHumidity();
    t = dht.readTemperature();

    //calculate dew point
    dp = dewPoint(h, t);

    //set fan
    if ((t-dp) <= DEWDELTA) {
      digitalWrite(FAN, HIGH);
    } else {
      digitalWrite(FAN, LOW);
    }

#ifdef DEBUG
    Serial.print(time);
    Serial.print(" | RH%: ");
    Serial.print(h);
    Serial.print(" | T°C: ");
    Serial.print(t);
    Serial.print(" | DP°C: ");
    Serial.print(dp);
    (digitalRead(FAN) == HIGH) ? Serial.println(" | ON") : Serial.println(" | OFF");
#endif
  }
}
