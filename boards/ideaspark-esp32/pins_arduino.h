#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include "soc/soc_caps.h"

// USB Configuration
#define USB_VID 0x1a86
#define USB_PID 0x7523

// OLED Display (I2C)
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C

// SPI Bus (RF modules, SD card)
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCK 18

// CC1101 RF Module (SubGhz)
#define CC1101_CS 5
#define CC1101_GDO0 16

// NRF24 Module
#define NRF24_CS 17
#define NRF24_CE 4

// SD Card
#define SDCARD_CS 4
#define SDCARD_MOSI 23
#define SDCARD_MISO 19
#define SDCARD_SCK 18

// Infrared
#define IR_TX_PIN 25
#define IR_RX_PIN 26

// Control Buttons
#define UP_BTN 34
#define DOWN_BTN 35
#define LEFT_BTN 32
#define RIGHT_BTN 33
#define SEL_BTN 27
#define ESC_BTN 14

// Battery Monitor (ADC)
#define BAT_PIN 36

// Serial (GPS/Debug)
#define SERIAL_TX 1
#define SERIAL_RX 3

// I2C Pins
static const uint8_t SDA = OLED_SDA;  // 21
static const uint8_t SCL = OLED_SCL;  // 22

// SPI Pins
static const uint8_t SS = CC1101_CS;   // 5
static const uint8_t MOSI = SPI_MOSI;  // 23
static const uint8_t MISO = SPI_MISO;  // 19
static const uint8_t SCK = SPI_SCK;    // 18

// UART Pins
static const uint8_t TX = SERIAL_TX;   // 1
static const uint8_t RX = SERIAL_RX;   // 3

// Analog Input Pins
static const uint8_t A0 = 36;
static const uint8_t A1 = 37;
static const uint8_t A2 = 38;
static const uint8_t A3 = 39;
static const uint8_t A4 = 32;
static const uint8_t A5 = 33;
static const uint8_t A6 = 34;
static const uint8_t A7 = 35;

// Touch Input Pins (Capacitive Touch)
static const uint8_t T0 = 4;
static const uint8_t T1 = 0;
static const uint8_t T2 = 2;
static const uint8_t T3 = 15;
static const uint8_t T4 = 13;
static const uint8_t T5 = 12;
static const uint8_t T6 = 14;
static const uint8_t T7 = 27;
static const uint8_t T8 = 33;
static const uint8_t T9 = 32;

#endif /* Pins_Arduino_h */
