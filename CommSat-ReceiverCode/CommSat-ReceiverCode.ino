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

// ⭐ HERE IS THE FIX: The function signature is updated
void OnDataRecv(const esp_now_recv_info * info, const uint8_t *incomingData, int len) {
  
  // Critical fix: Check if the data length matches the struct size
  if (len == sizeof(receivedData)) {
    memcpy(&receivedData, incomingData, sizeof(receivedData));

    Serial.println("Data Received:");
    
    // If you need the sender's MAC address, you can get it from the 'info' struct
    // Serial.print("Received from: ");
    // for (int i = 0; i < 6; i++) {
    //   Serial.printf("%02X", info->src_addr[i]);
    //   if (i < 5) Serial.print(":");
    // }
    // Serial.println();

    Serial.print("Temperature: "); Serial.println(receivedData.temperature);
    Serial.print("Pressure: "); Serial.println(receivedData.pressure);
    Serial.print("Humidity: "); Serial.println(receivedData.humidity);
    Serial.print("Accel X: "); Serial.println(receivedData.accelX);
    Serial.print("Accel Y: "); Serial.println(receivedData.accelY);
    Serial.print("Accel Z: "); Serial.println(receivedData.accelZ);
    Serial.println("-----------");

  } else {
    // If lengths don't match, print an error to prevent crashes
    Serial.println("Error: Received data length mismatch.");
    Serial.print("Expected: "); Serial.print(sizeof(receivedData));
    Serial.print(" bytes | Received: "); Serial.println(len);
    Serial.println("-----------");
  }
}

void setup() {
  Serial.begin(115200);

  // --- Start Fix ---
  // Set WiFi to station mode AND disconnect.
  // This forces a full re-initialization of the WiFi stack,
  // which fixes the "00:00:00..." MAC address bug.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); 
  delay(100); // Wait 100ms for the radio to stabilize
  // --- End Fix ---

  Serial.print("Receiver MAC: ");
  Serial.println(WiFi.macAddress()); // This should now print the REAL MAC

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
  // Nothing needed here
}