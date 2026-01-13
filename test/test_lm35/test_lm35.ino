#define LM35_PIN 34

void setup() {
  Serial.begin(115200);
}

void loop() {
  int adc = analogRead(LM35_PIN);
  float voltage = adc * (3.3 / 4095.0);
  float temperature = voltage * 100; // LM35 = 10mV/°C

  Serial.print("LM35 Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000);
}
