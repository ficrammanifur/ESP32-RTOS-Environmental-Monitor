#define LDR_PIN 34
#define LED_PIN 33

int readLDR() {
  long sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += analogRead(LDR_PIN);
    delay(2);
  }
  return sum / 20;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogReadResolution(12);
}

void loop() {
  int ldr = readLDR();

  Serial.print("LDR filtered = ");
  Serial.println(ldr);

  if (ldr < 200) digitalWrite(LED_PIN, HIGH);
  else digitalWrite(LED_PIN, LOW);

  delay(500);
}
