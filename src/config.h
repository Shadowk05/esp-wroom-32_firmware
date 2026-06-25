#ifndef CONFIG_H
#define CONFIG_H

// Board Configuration
#define BOARD_NAME "Ideaspark ESP32 OLED"
#define FIRMWARE_VERSION "1.0.0"
#define BUILD_DATE __DATE__ " " __TIME__

// Display Settings
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_I2C_ADDR 0x3C

// WiFi Settings
#define WIFI_SSID_PREFIX "BRUCE"
#define MAX_WIFI_NETWORKS 50

// BLE Settings
#define BLE_DEVICE_NAME "Bruce_ESP32"

// RF Settings
#define RF_FREQ_DEFAULT 433920000  // 433.92 MHz
#define RF_POWER_DEFAULT 10

// Battery Settings
#define BATTERY_MIN_VOLTAGE 3.0
#define BATTERY_MAX_VOLTAGE 4.2
#define BATTERY_CRITICAL 10  // Percentage

// Memory Settings
#define USE_LITE_VERSION 1  // Save memory
#define MAX_LOG_ENTRIES 100

// Debug Settings
#define DEBUG_SERIAL 1
#define DEBUG_BAUD 115200

#endif // CONFIG_H
