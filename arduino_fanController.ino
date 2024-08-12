#define FAN 2
#define BAUDRATE 115200

void setup() {
  pinMode(FAN, OUTPUT);
  Serial.begin(BAUDRATE);
}

void loop() {
  digitalWrite(FAN, HIGH);
  Serial.print(millis());
  Serial.println(" ON");
  delay(3000);
  digitalWrite(FAN, LOW);
  Serial.print(millis());
  Serial.println(" OFF");
  delay(3000);
}
