#define FAN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(FAN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(FAN, HIGH);
  delay(3000);
  digitalWrite(FAN, LOW);
  delay(3000);
}
