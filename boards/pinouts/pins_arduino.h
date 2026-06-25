#ifndef PINOUTS_H
#define PINOUTS_H

// This file includes board-specific pin definitions
// Based on the selected board configuration

#if defined(IDEASPARK_ESP32)
    #include "../ideaspark-esp32/pins_arduino.h"
#elif defined(ESP_GENERAL)
    #include "../ESP-General/pins_arduino.h"
#else
    // Default fallback pins for generic ESP32
    #define OLED_SDA 21
    #define OLED_SCL 22
    #define SPI_MOSI 23
    #define SPI_MISO 19
    #define SPI_SCK 18
    #define CC1101_CS 5
    #define IR_TX_PIN 25
    #define IR_RX_PIN 26
    #define BAT_PIN 36
#endif

#endif // PINOUTS_H
