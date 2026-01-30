#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=== ESP-HACK-T-Embed ===");
    Serial.println("Simple test build");
    Serial.printf("Chip ID: %08X\n", (uint32_t)ESP.getEfuseMac());
}

void loop() {
    static int counter = 0;
    Serial.printf("Counter: %d, Free heap: %d\n", 
                  counter++, 
                  ESP.getFreeHeap());
    delay(1000);
}
