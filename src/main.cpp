#include <Arduino.h>
#include "CONFIG.h"

// Переменные для энкодера
volatile int encoderPos = 0;
int lastEncoded = 0;
unsigned long lastEncoderTime = 0;

// Обработчик прерываний энкодера
void IRAM_ATTR readEncoder() {
  int MSB = digitalRead(ENC_A);
  int LSB = digitalRead(ENC_B);
  
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;
  
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderPos++;
  } else if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderPos--;
  }
  
  lastEncoded = encoded;
  lastEncoderTime = millis();
}

void setup() {
  // Инициализация Serial
  Serial.begin(115200);
  delay(1000); // Дать время для подключения Serial
  
  Serial.println("\n\n=== ESP-HACK T-Embed with Encoder ===");
  Serial.printf("Chip Model: ESP32-S3\n");
  Serial.printf("Chip ID: %08X\n", (uint32_t)ESP.getEfuseMac());
  Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  
  // Проверка PSRAM
  if (psramFound()) {
    Serial.printf("PSRAM Size: %d MB\n", ESP.getPsramSize() / (1024 * 1024));
    Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
  } else {
    Serial.println("PSRAM not found!");
  }
  
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
  
  // Инициализация пинов
  Serial.println("\n=== Pin Initialization ===");
  
  // Энкодер
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_BTN, INPUT_PULLUP);
  
  // Прикрепляем прерывания для энкодера
  attachInterrupt(digitalPinToInterrupt(ENC_A), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), readEncoder, CHANGE);
  
  Serial.printf("Encoder: A=%d, B=%d, BTN=%d\n", ENC_A, ENC_B, ENC_BTN);
  
  // Дополнительные кнопки
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  Serial.printf("Buttons: BTN1=%d, BTN2=%d\n", BTN_1, BTN_2);
  
  // CC1101 пины
  pinMode(CC1101_CS, OUTPUT);
  digitalWrite(CC1101_CS, HIGH); // Отключить по умолчанию
  Serial.printf("CC1101: CS=%d, GDO0=%d, GDO2=%d\n", CC1101_CS, CC1101_GDO0, CC1101_GDO2);
  
  // TFT подсветка
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // Включить подсветку
  Serial.printf("TFT: CS=%d, DC=%d, BL=%d\n", TFT_CS, TFT_DC, TFT_BL);
  
  Serial.println("\n=== System Ready ===");
  Serial.println("Rotate encoder or press buttons...");
}

void loop() {
  static int lastEncoderPos = 0;
  static unsigned long lastPrintTime = 0;
  
  // Проверка энкодера
  if (encoderPos != lastEncoderPos) {
    Serial.printf("Encoder: %d (delta: %d)\n", encoderPos, encoderPos - lastEncoderPos);
    lastEncoderPos = encoderPos;
  }
  
  // Проверка кнопки энкодера
  static bool lastBtnState = HIGH;
  bool btnState = digitalRead(ENC_BTN);
  if (btnState != lastBtnState) {
    if (btnState == LOW) {
      Serial.println("Encoder button PRESSED");
    } else {
      Serial.println("Encoder button RELEASED");
    }
    lastBtnState = btnState;
    delay(50); // Дебаунс
  }
  
  // Проверка дополнительных кнопок
  if (digitalRead(BTN_1) == LOW) {
    Serial.println("Button 1 pressed");
    delay(300); // Дебаунс
  }
  
  if (digitalRead(BTN_2) == LOW) {
    Serial.println("Button 2 pressed");
    delay(300); // Дебаунс
  }
  
  // Периодический вывод состояния
  if (millis() - lastPrintTime > 5000) {
    lastPrintTime = millis();
    Serial.printf("Status: Encoder=%d, Heap=%d, PSRAM=%d\n",
                  encoderPos, ESP.getFreeHeap(), 
                  psramFound() ? ESP.getFreePsram() : 0);
  }
  
  delay(10); // Небольшая задержка
}
  attachInterrupt(digitalPinToInterrupt(ENC_A), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), readEncoder, CHANGE);
  
  Serial.printf("Encoder: A=%d, B=%d, BTN=%d\n", ENC_A, ENC_B, ENC_BTN);
  
  // Дополнительные кнопки
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  Serial.printf("Buttons: BTN1=%d, BTN2=%d\n", BTN_1, BTN_2);
  
  // CC1101 пины
  pinMode(CC1101_CS, OUTPUT);
  digitalWrite(CC1101_CS, HIGH); // Отключить по умолчанию
  Serial.printf("CC1101: CS=%d, GDO0=%d, GDO2=%d\n", CC1101_CS, CC1101_GDO0, CC1101_GDO2);
  
  // TFT подсветка
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // Включить подсветку
  Serial.printf("TFT: CS=%d, DC=%d, BL=%d\n", TFT_CS, TFT_DC, TFT_BL);
  
  Serial.println("\n=== System Ready ===");
  Serial.println("Rotate encoder or press buttons...");
}

void loop() {
  static int lastEncoderPos = 0;
  static unsigned long lastPrintTime = 0;
  
  // Проверка энкодера
  if (encoderPos != lastEncoderPos) {
    Serial.printf("Encoder: %d (delta: %d)\n", encoderPos, encoderPos - lastEncoderPos);
    lastEncoderPos = encoderPos;
  }
  
  // Проверка кнопки энкодера
  static bool lastBtnState = HIGH;
  bool btnState = digitalRead(ENC_BTN);
  if (btnState != lastBtnState) {
    if (btnState == LOW) {
      Serial.println("Encoder button PRESSED");
    } else {
      Serial.println("Encoder button RELEASED");
    }
    lastBtnState = btnState;
    delay(50); // Дебаунс
  }
  
  // Проверка дополнительных кнопок
  if (digitalRead(BTN_1) == LOW) {
    Serial.println("Button 1 pressed");
    delay(300); // Дебаунс
  }
  
  if (digitalRead(BTN_2) == LOW) {
    Serial.println("Button 2 pressed");
    delay(300); // Дебаунс
  }
  
  // Периодический вывод состояния
  if (millis() - lastPrintTime > 5000) {
    lastPrintTime = millis();
    Serial.printf("Status: Encoder=%d, Heap=%d, PSRAM=%d\n",
                  encoderPos, ESP.getFreeHeap(), 
                  psramFound() ? ESP.getFreePsram() : 0);
  }
  
  delay(10); // Небольшая задержка
}
