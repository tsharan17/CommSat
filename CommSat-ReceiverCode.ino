#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  float temperature;
  float pressure;
  float humidity;
  float accelX;
  float accelY;
  float accelZ;
} struct_message;

struct_message receivedData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));

  Serial.println("Data Received:");
  Serial.print("Temperature: "); Serial.println(receivedData.temperature);
  Serial.print("Pressure: "); Serial.println(receivedData.pressure);
  Serial.print("Humidity: "); Serial.println(receivedData.humidity);
  Serial.print("Accel X: "); Serial.println(receivedData.accelX);
  Serial.print("Accel Y: "); Serial.println(receivedData.accelY);
  Serial.print("Accel Z: "); Serial.println(receivedData.accelZ);
  Serial.println("-----------");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing needed here
}
