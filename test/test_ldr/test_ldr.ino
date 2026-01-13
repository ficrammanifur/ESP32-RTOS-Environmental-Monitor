#define LDR_PIN 32

void setup() {
  Serial.begin(115200);
}

void loop() {
  int lightValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(lightValue);
  delay(1000);
}
