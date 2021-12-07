void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  delay(1000);
}
