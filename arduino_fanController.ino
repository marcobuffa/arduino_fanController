#define FAN 2
#define BAUDRATE 115200

static unsigned int currentTime = 0;
static unsigned int time;

void setup() {
  pinMode(FAN, OUTPUT);
  Serial.begin(BAUDRATE);
}

void loop() {
  time = millis();
  if ((time - currentTime) >= 3000){
    currentTime = time;
    if (digitalRead(FAN) == HIGH){
      digitalWrite(FAN, LOW);
      Serial.println("OFF");
    } else {
      digitalWrite(FAN, HIGH);
      Serial.println("ON");
    }
    Serial.println(time);
  }
}
