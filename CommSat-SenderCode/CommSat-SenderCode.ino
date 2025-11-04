#include <WiFi.h>
#include <esp_now.h>

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ==== DHT11 Setup ====
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ==== BMP280 Setup ====
Adafruit_BMP280 bmp;

// ==== MPU6050 Setup ====
Adafruit_MPU6050 mpu;

// ==== ESP-NOW Setup ====
uint8_t receiverAddress[] = {0x00, 0x4B, 0x12, 0x34, 0x44, 0x6C}; // CHANGE THIS to your receiver MAC 00:4B:12:34:44:6C

typedef struct struct_message {
  float temperature;
  float pressure;
  float humidity;
  float accelX;
  float accelY;
  float accelZ;
} struct_message;

struct_message dataToSend;

// Callback when data is sent
// Callback when data is sent
// ⭐ HERE IS THE FIX: The function signature is updated
void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");

  // Init DHT11
  dht.begin();
  Serial.println("DHT11 initialized.");

  // Init BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found! Skipping...");
  } else {
    Serial.println("BMP280 initialized.");
  }

  // Init MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found! Skipping...");
  } else {
    Serial.println("MPU6050 initialized.");
  }

  // Init WiFi and ESP-NOW
  WiFi.mode(WIFI_STA);
  Serial.print("Sender MAC Address: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  Serial.println("ESP-NOW initialized.");

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  Serial.println("Peer added successfully.");
}

void loop() {
  // Read DHT
  dataToSend.temperature = dht.readTemperature();
  dataToSend.humidity = dht.readHumidity();

  // Read BMP280 (if initialized)
  dataToSend.pressure = bmp.readPressure() / 100.0F;

  // Read MPU6050 (if initialized)
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  dataToSend.accelX = a.acceleration.x;
  dataToSend.accelY = a.acceleration.y;
  dataToSend.accelZ = a.acceleration.z;

  // Send Data
  esp_now_send(receiverAddress, (uint8_t *)&dataToSend, sizeof(dataToSend));

  // Debug Output
  Serial.println("Data Sent:");
  Serial.printf("Temp: %.2f °C | Hum: %.2f %% | Pressure: %.2f hPa\n", dataToSend.temperature, dataToSend.humidity, dataToSend.pressure);
  Serial.printf("Accel: X=%.2f Y=%.2f Z=%.2f\n", dataToSend.accelX, dataToSend.accelY, dataToSend.accelZ);
  Serial.println("--------------------------------------------------");

  delay(2000);
}


