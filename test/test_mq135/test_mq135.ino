#define MQ135_PIN 35

void setup() {
  Serial.begin(115200);
}

void loop() {
  int gasValue = analogRead(MQ135_PIN);
  Serial.print("MQ-135 ADC: ");
  Serial.println(gasValue);
  delay(1000);
}
