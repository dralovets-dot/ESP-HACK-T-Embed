#ifndef PIN_H
#define PIN_H

// === Lilygo T-Embed Pin Configuration ===
// На основе документации: энкодер + 2 кнопки

// Display (TFT) - SPI дисплей
#define TFT_CS    5
#define TFT_DC    15
#define TFT_RST   -1   // Reset не используется, управляется по SPI
#define TFT_BL    38   // Подсветка
#define TFT_SCLK  6    // SPI CLK
#define TFT_MOSI  7    // SPI MOSI
#define TFT_MISO  8    // SPI MISO

// Энкодер (Encoder + Button)
#define ENC_A     0    // Энкодер канал A (поворот)
#define ENC_B     14   // Энкодер канал B (поворот)  
#define ENC_BTN   21   // Кнопка энкодера (нажатие)

// Дополнительные кнопки (2 шт)
#define BTN_1     47   // Кнопка 1 (сенсорная?)
#define BTN_2     48   // Кнопка 2 (сенсорная?)

// Для совместимости со старым кодом (маппинг)
#define BUTTON_UP    ENC_A      // Для навигации вверх
#define BUTTON_DOWN  ENC_B      // Для навигации вниз  
#define BUTTON_OK    ENC_BTN    // Подтверждение
#define BUTTON_BACK  BTN_1      // Назад/отмена

// CC1101 (Radio модуль) - SPI через HSPI
#define CC1101_GDO0  9    // GDO0
#define CC1101_GDO2  10   // GDO2  
#define CC1101_CS    13   // Chip Select
#define CC1101_SCK   12   // SPI Clock (HSPI)
#define CC1101_MOSI  11   // SPI MOSI (HSPI)
#define CC1101_MISO  3    // SPI MISO (HSPI)

// SD Card (если есть)
#define SD_CS     4
#define SD_SCLK   6    // Совмещен с TFT
#define SD_MOSI   7    // Совмещен с TFT  
#define SD_MISO   8    // Совмещен с TFT

// Инфракрасный (IR)
#define IR_TX    16
#define IR_RX    17

// I2C
#define I2C_SCL  18
#define I2C_SDA  19

// Serial
#define TX_PIN   43
#define RX_PIN   44

// === Display Settings ===
#define SCREEN_WIDTH  170
#define SCREEN_HEIGHT 320
#define ORIENTATION   1  // 0-3 для поворота

// === Board Features ===
#define HAS_PSRAM     1   // Есть PSRAM
#define HAS_TFT       1   // Есть TFT дисплей
#define HAS_CC1101    1   // Есть CC1101 радио
#define HAS_ENCODER   1   // Есть энкодер
#define HAS_SD_CARD   0   // Возможно нет SD слота
#define HAS_TOUCH     1   // Есть сенсорная кнопка?

#endif
#define RX_PIN   44

// === Display Settings ===
#define SCREEN_WIDTH  170
#define SCREEN_HEIGHT 320
#define ORIENTATION   1  // 0-3 для поворота

// === Board Features ===
#define HAS_PSRAM     1   // Есть PSRAM
#define HAS_TFT       1   // Есть TFT дисплей
#define HAS_CC1101    1   // Есть CC1101 радио
#define HAS_ENCODER   1   // Есть энкодер
#define HAS_SD_CARD   0   // Возможно нет SD слота
#define HAS_TOUCH     1   // Есть сенсорная кнопка?

#endif
