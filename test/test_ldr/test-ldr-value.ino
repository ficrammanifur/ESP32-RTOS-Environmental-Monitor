#define LDR_PIN 34   // GPIO 34 (ADC)

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  delay(500);
}
