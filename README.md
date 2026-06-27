# Bruce Firmware for Ideaspark ESP-WROOM-32 with OLED

A customized port of the [Bruce firmware](https://github.com/BruceDevices/firmware) designed specifically for the **Ideaspark ESP-WROOM-32** microcontroller with integrated OLED display.

## Hardware Specifications

### Board
- **MCU**: ESP32 (Dual-core 240MHz Xtensa L106)
- **Flash Memory**: 4MB
- **RAM**: 520KB SRAM
- **Display**: 0.96" OLED 128x64 pixels (I2C interface)
- **USB**: USB-C for programming and power

### Pinout Configuration

#### I2C (OLED Display)
- **SDA**: GPIO 21
- **SCL**: GPIO 22
- **Address**: 0x3C

#### SPI Bus (Modules)
- **MOSI**: GPIO 23
- **MISO**: GPIO 19
- **SCK**: GPIO 18

#### RF Modules
- **CC1101 (SubGhz)**: CS=GPIO 5, GDO0=GPIO 16
- **NRF24**: CS=GPIO 17, CE=GPIO 4

#### I/O
- **IR TX**: GPIO 25
- **IR RX**: GPIO 26
- **Battery Monitor**: GPIO 36 (ADC)

#### Control Buttons
- **UP**: GPIO 34
- **DOWN**: GPIO 35
- **LEFT**: GPIO 32
- **RIGHT**: GPIO 33
- **SELECT**: GPIO 27
- **ESC**: GPIO 14

#### SD Card (Optional)
- **CS**: GPIO 4
- **MOSI**: GPIO 23
- **MISO**: GPIO 19
- **SCK**: GPIO 18

#### Serial (GPS/Debug)
- **TX**: GPIO 1
- **RX**: GPIO 3

## Features

### Supported
✅ WiFi Scanning & Attacks (Deauth, Beacon Spam, Evil Portal)  
✅ BLE Scanning & Attacks (Spam, BadBLE)  
✅ RF SubGhz (CC1101 module support)  
✅ Infrared (TX/RX with custom protocols)  
✅ RFID/NFC (PN532 via I2C)  
✅ BadUSB (Ducky script execution)  
✅ Web UI (Remote control)  
✅ OLED Display (128x64 I2C)  
✅ Battery Monitoring  
✅ SD Card Support (Optional)  

### Not Supported (Memory Constraints)
❌ FM Radio  
❌ LoRa  
❌ NRF24 (unless SD card disabled)  
❌ Large file operations  

## Prerequisites

### Software
- [PlatformIO Core](https://platformio.org/install/cli) or [PlatformIO IDE](https://platformio.org/install/ide)
- Python 3.6+
- Git

### Hardware
- Ideaspark ESP-WROOM-32 board
- USB-C cable for programming
- Optional: CC1101 or NRF24 module for RF features
- Optional: PN532 module for RFID/NFC

## Installation & Building

### 1. Clone the Repository
```bash
git clone https://github.com/Shadowk05/esp-wroom-32_firmware.git
cd esp-wroom-32_firmware
```

### 2. Build with PlatformIO
```bash
# Build for Ideaspark ESP32
pio run -e ideaspark-esp32

# Or using the shorthand
pio run
```

### 3. Upload to Device

#### First Time Setup (Erase Flash)
```bash
pio run -e ideaspark-esp32 -t erase
pio run -e ideaspark-esp32 -t upload
```

#### Regular Upload
```bash
pio run -e ideaspark-esp32 -t upload
```

#### Using esptool.py Directly
```bash
# Erase flash
esptool.py --port /dev/ttyUSB0 erase_flash

# Flash binary
esptool.py --port /dev/ttyUSB0 write_flash 0x00000 .pio/build/ideaspark-esp32/firmware.bin
```

### 4. Monitor Serial Output
```bash
pio device monitor -e ideaspark-esp32
```

## Configuration

### Modifying GPIO Pins

Edit `boards/ideaspark-esp32/pins_arduino.h` to change pin assignments:

```cpp
// Example: Change IR TX pin
#define IR_TX_PIN 25  // Change to desired GPIO
```

### Enabling/Disabling Features

Edit `boards/ideaspark-esp32/ideaspark-esp32.ini` build flags:

```ini
; Enable RFID support
-DFEATURE_RFID=1

; Enable NRF24
-DFEATURE_NRF24=1
```

### Adjusting OLED Configuration

The OLED is configured via I2C at address `0x3C`. If your display has a different address, update:

```cpp
#define OLED_ADDR 0x3D  // Default is 0x3C
```

## Memory Optimization

The Ideaspark board has limited flash (4MB) and RAM (520KB). The firmware uses:

- **Lite Version** compilation flags to disable non-essential features
- **Function sections** and **data sections** for garbage collection
- **Memory-efficient** display driver
- **Selective feature compilation** via build flags

## Troubleshooting

### Upload Fails
1. Check USB cable connection
2. Verify COM port: `pio device list`
3. Try forcing bootloader: Hold BOOT button while plugging in USB
4. Erase flash: `pio run -t erase`

### OLED Not Displaying
1. Check I2C pins (SDA=21, SCL=22)
2. Verify I2C address (default 0x3C)
3. Check pull-up resistors on I2C bus
4. Monitor serial output for I2C errors

### Compilation Errors
1. Update PlatformIO: `pio platform update`
2. Clean build: `pio run --target clean`
3. Check for missing dependencies: `pio run --verbose`

### WiFi/BLE Not Working
1. Ensure antenna is connected (if applicable)
2. Check power supply (USB should provide sufficient power)
3. Review RF module connections
4. Check serial output for module initialization errors

## Resources

- [Bruce Firmware Wiki](https://wiki.bruce.computer/)
- [ESP32 Documentation](https://docs.espressif.com/)
- [PlatformIO Documentation](https://docs.platformio.org/)
- [Arduino-ESP32 Reference](https://docs.espressif.com/projects/arduino-esp32/en/latest/)

## Contributing

Feel free to submit issues and enhancement requests! Pull requests are welcome.

## License

This project is licensed under the **GNU Affero General Public License v3.0** - see the LICENSE file for details.

**Important**: This firmware is intended for legal, authorized security testing purposes only. Unauthorized use of WiFi attacks, RF jamming, or other offensive features may violate local laws and regulations.

## Disclaimer

This firmware is provided as-is for educational and authorized security research purposes. The author is not responsible for misuse, damage, or legal consequences arising from the use of this software. Always ensure you have proper authorization before conducting any security testing.

## Support

For issues specific to this port, please open an issue on GitHub.  
For Bruce firmware general questions, visit the [Bruce Discord](https://discord.gg/WJ9XF9czVT).
