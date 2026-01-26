#define LDR_PIN 34   // Pin LDR (ADC only)

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);

  // Interpretasi nilai LDR (sesuai kode asli kamu)
  String ldrStatus = (ldrValue > 800) ? "GELAP" :
                     (ldrValue < 450) ? "TERANG" :
                                        "SEDANG";

  Serial.println("========== LDR ==========");
  Serial.print("LDR Value  : ");
  Serial.println(ldrValue);
  Serial.print("LDR Status : ");
  Serial.println(ldrStatus);

  delay(1000);
}
