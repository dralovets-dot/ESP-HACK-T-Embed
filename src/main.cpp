#include <Arduino.h>
#include <SPI.h>
#include <CC1101.h>
#include <Wire.h>
#include <TFT_eSPI.h>

// Конфигурация для T-Embed CC1101
#define TFT_BL 38
#define TFT_WIDTH 170
#define TFT_HEIGHT 320

// Пины для CC1101 на T-Embed
#define CC1101_CS 10
#define CC1101_GDO0 9
#define CC1101_GDO2 8

TFT_eSPI tft = TFT_eSPI();
CC1101 radio;

// Конфигурация CC1101 для T-Embed
CC1101Settings settings = {
    .frequency = 433.92,  // MHz
    .dataRate = 1.2,      // kbps
    .rxBandwidth = 58,    // kHz
    .deviation = 35.6,    // kHz
    .power = 12,          // dBm
    .syncMode = 0,
    .preambleLength = 4,
    .packetLength = 255
};

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("ESP-HACK для LilyGO T-Embed CC1101");
    Serial.println("===================================");
    
    // Инициализация дисплея
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("ESP-HACK T-Embed", 10, 10, 2);
    tft.drawString("CC1101 RF Tool", 10, 40, 2);
    
    // Инициализация CC1101
    SPI.begin(2, 12, 13, 10); // SCK, MISO, MOSI, CS
    if (radio.begin(CC1101_CS, CC1101_GDO0, CC1101_GDO2)) {
        Serial.println("CC1101 инициализирован успешно");
        tft.drawString("CC1101: OK", 10, 80, 2);
        
        // Настройка параметров
        radio.setSettings(&settings);
        radio.setRXState();
        
        tft.drawString("Частота: 433.92 MHz", 10, 110, 2);
        tft.drawString("Скорость: 1.2 kbps", 10, 130, 2);
    } else {
        Serial.println("Ошибка инициализации CC1101");
        tft.drawString("CC1101: ERROR", 10, 80, 2);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.drawString("Проверьте подключение", 10, 100, 2);
    }
    
    tft.drawString("Жду данные...", 10, 170, 2);
}

void loop() {
    // Проверка входящих данных
    if (radio.checkReceiveFlag()) {
        uint8_t buffer[256];
        uint8_t length = radio.receiveData(buffer, sizeof(buffer));
        
        if (length > 0) {
            Serial.print("Получено байт: ");
            Serial.println(length);
            
            // Отображение на дисплее
            tft.fillRect(10, 190, 300, 100, TFT_BLACK);
            tft.drawString("Получены данные:", 10, 190, 2);
            
            // HEX вывод
            char hexStr[10];
            for (int i = 0; i < min(length, 8); i++) {
                sprintf(hexStr, "%02X ", buffer[i]);
                tft.drawString(hexStr, 10 + (i * 25), 220, 2);
            }
            
            // ASCII вывод
            tft.drawString("ASCII:", 10, 250, 2);
            for (int i = 0; i < min(length, 8); i++) {
                char asciiChar = (buffer[i] >= 32 && buffer[i] <= 126) ? buffer[i] : '.';
                tft.drawChar(asciiChar, 10 + (i * 15), 270, 2);
            }
            
            // Отправка эхо
            radio.transmitData(buffer, length);
            tft.drawString("Эхо отправлено", 10, 300, 2);
            delay(1000);
            tft.fillRect(10, 300, 150, 20, TFT_BLACK);
        }
    }
    
    // Кнопки T-Embed для управления
    static unsigned long lastButtonCheck = 0;
    if (millis() - lastButtonCheck > 100) {
        lastButtonCheck = millis();
        
        // Кнопка BOOT (GPIO0)
        if (digitalRead(0) == LOW) {
            tft.fillRect(10, 150, 200, 20, TFT_BLACK);
            tft.drawString("Тестовая передача", 10, 150, 2);
            
            uint8_t testData[] = {0xAA, 0x55, 0x01, 0x02, 0x03};
            radio.transmitData(testData, sizeof(testData));
            delay(100);
        }
    }
    
    delay(10);
}

// Дополнительные функции для RF анализа
void scanFrequencies() {
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Сканирование частот...", 10, 10, 2);
    
    float frequencies[] = {433.92, 434.42, 868.35, 915.0};
    
    for (int i = 0; i < 4; i++) {
        settings.frequency = frequencies[i];
        radio.setSettings(&settings);
        radio.setRXState();
        
        delay(100);
        
        int rssi = radio.getRSSI();
        char buffer[50];
        sprintf(buffer, "%.2f MHz: %d dBm", frequencies[i], rssi);
        tft.drawString(buffer, 10, 40 + (i * 20), 2);
        
        Serial.println(buffer);
    }
}