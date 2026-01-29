// LilyGO T-Embed specific setup
#define ST7789_DRIVER
#define TFT_WIDTH  170
#define TFT_HEIGHT 320

#define TFT_MISO  -1  // Not connected
#define TFT_MOSI  11
#define TFT_SCLK  12
#define TFT_CS    13
#define TFT_DC    14
#define TFT_RST   21
#define TFT_BL    38

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SPI_FREQUENCY  40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
