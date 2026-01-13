#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <DHT.h>

// ===== PIN CONFIG =====
#define MQ135_PIN  35
#define LM35_PIN   32
#define LDR_PIN    34
#define DHT_PIN    27
#define LED_PIN    33

// ===== ThingSpeak =====
String apiKey = "ISI_API_KEY_KAMU";

// ===== DHT =====
#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

// ===== FreeRTOS =====
QueueHandle_t sensorQueue;
SemaphoreHandle_t serialMutex;

// ===== Struct =====
typedef struct {
  float temperature;
  float humidity;
  int gas;
  int light;
} SensorData;

// ===== ADC Averaging =====
int readADCAvg(int pin) {
  long sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / 20;
}

// ===== SENSOR TASK =====
void sensorTask(void *pv) {
  SensorData data;

  while (1) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));

    data.gas = readADCAvg(MQ135_PIN);

    int lm35_adc = readADCAvg(LM35_PIN);
    float lm35_temp = (lm35_adc * 3.3 / 4095.0) * 100.0;

    float dht_temp = dht.readTemperature();
    data.humidity = dht.readHumidity();
    data.temperature = (lm35_temp + dht_temp) / 2.0;

    data.light = readADCAvg(LDR_PIN);
    data.light = map(data.light, 0, 500, 0, 100);
    data.light = constrain(data.light, 0, 100);

    xSemaphoreTake(serialMutex, portMAX_DELAY);
    Serial.println("=== SENSOR DATA ===");
    Serial.printf("Temp: %.2f C\n", data.temperature);
    Serial.printf("Humidity: %.2f %%\n", data.humidity);
    Serial.printf("Gas ADC: %d\n", data.gas);
    Serial.printf("Light: %d %%\n", data.light);
    Serial.println("===================");
    xSemaphoreGive(serialMutex);

    xQueueSend(sensorQueue, &data, portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// ===== IOT TASK =====
void iotTask(void *pv) {
  SensorData data;

  while (1) {
    if (xQueueReceive(sensorQueue, &data, portMAX_DELAY)) {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        String url = "http://api.thingspeak.com/update?api_key=" + apiKey +
                     "&field1=" + String(data.temperature) +
                     "&field2=" + String(data.humidity) +
                     "&field3=" + String(data.gas) +
                     "&field4=" + String(data.light);

        http.begin(url);
        http.GET();
        http.end();
      }
    }
    vTaskDelay(pdMS_TO_TICKS(15000));
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  pinMode(LED_PIN, OUTPUT);

  dht.begin();

  // ===== WiFiManager =====
  WiFiManager wm;
  wm.setConfigPortalTimeout(180);
  bool res = wm.autoConnect("ESP32-EnvSentinel");

  if (!res) {
    Serial.println("WiFi gagal, restart...");
    ESP.restart();
  }

  Serial.println("WiFi Connected!");

  sensorQueue = xQueueCreate(5, sizeof(SensorData));
  serialMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(sensorTask, "SensorTask", 4096, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(iotTask, "IoTTask", 4096, NULL, 1, NULL, 1);
}

void loop() {}
