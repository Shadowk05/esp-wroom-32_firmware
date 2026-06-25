# Ideaspark ESP-WROOM-32 with OLED - Connections Guide

## Overview
This document details all the connections and pinouts for adding RF modules and accessories to your Ideaspark ESP-WROOM-32 OLED board.

## Default Pinout

### I2C Bus (OLED Display)
| Signal | GPIO |
|--------|------|
| SDA    | 21   |
| SCL    | 22   |
| GND    | GND  |
| 3.3V   | 3.3V |

### SPI Bus (RF Modules)
| Signal | GPIO |
|--------|------|
| MOSI   | 23   |
| MISO   | 19   |
| SCK    | 18   |
| GND    | GND  |
| 3.3V   | 3.3V |

## Adding RF Modules

### CC1101 SubGhz Module
```
CC1101 Pin   →  ESP32 GPIO
VCC          →  3.3V
GND          →  GND
SI/MOSI      →  23 (SPI MOSI)
SO/MISO      →  19 (SPI MISO)
CLK/SCK      →  18 (SPI SCK)
CS/NSS       →  5
GDO0         →  16
GDO2         →  (not used, can leave floating)
```

### NRF24L01+ Module
```
NRF24 Pin    →  ESP32 GPIO
VCC          →  3.3V (with 10µF capacitor!)
GND          →  GND
MOSI         →  23 (SPI MOSI)
MISO         →  19 (SPI MISO)
SCK          →  18 (SPI SCK)
CSN          →  17
CE           →  4
IRQ          →  (optional)
```

**Important**: The NRF24 requires a **10µF capacitor** between VCC and GND due to high current spikes during transmission.

## Adding RFID/NFC Module

### PN532 (I2C Mode)
```
PN532 Pin    →  ESP32 GPIO
VCC          →  3.3V
GND          →  GND
SDA          →  21 (I2C SDA)
SCL          →  22 (I2C SCL)
```

### PN532 (SPI Mode - Alternative)
```
PN532 Pin    →  ESP32 GPIO
VCC          →  3.3V
GND          →  GND
SI/MOSI      →  23 (SPI MOSI)
SO/MISO      →  19 (SPI MISO)
SCK          →  18 (SPI SCK)
CS           →  15
```

## Adding SD Card Module

### SD Card Adapter (SPI Mode)
```
SD Pin       →  ESP32 GPIO
VCC          →  3.3V
GND          →  GND
MOSI         →  23 (SPI MOSI)
MISO         →  19 (SPI MISO)
SCK          →  18 (SPI SCK)
CS           →  4
```

**Note**: SD card and NRF24 share the CS pin (GPIO 4). You can only use one or wire them to different pins.

## IR Transmitter/Receiver

### IR LED (Transmitter)
```
IR LED Anode  →  GPIO 25 (via 100Ω resistor)
IR LED Cathode →  GND
```

### IR Receiver (38kHz)
```
Receiver VCC  →  3.3V
Receiver GND  →  GND
Receiver OUT  →  GPIO 26
```

## Control Buttons (with Pull-up Resistors)

| Button  | GPIO | Notes          |
|---------|------|----------------|
| UP      | 34   | Pull-up 10kΩ   |
| DOWN    | 35   | Pull-up 10kΩ   |
| LEFT    | 32   | Pull-up 10kΩ   |
| RIGHT   | 33   | Pull-up 10kΩ   |
| SELECT  | 27   | Pull-up 10kΩ   |
| ESC     | 14   | Pull-up 10kΩ   |

Connect button between GPIO and GND (active low).

## Battery Monitoring

### Single-Cell LiPo Battery
```
Battery +    →  GPIO 36 (via 180kΩ/180kΩ voltage divider)
Battery -    →  GND
```

**Voltage Divider Calculation**:
- Input: 4.2V max (LiPo charged)
- Output: 2.1V (ESP32 ADC max ~3.3V)
- Resistors: 180kΩ / 180kΩ

## GPS Module (Optional)

### Serial GPS Module
```
GPS VCC      →  3.3V / 5V (check module specs)
GPS GND      →  GND
GPS TX       →  GPIO 3 (ESP32 RX)
GPS RX       →  GPIO 1 (ESP32 TX)
```

## Recommended Component List

### Essential
- 2x 10kΩ resistors (I2C pull-ups)
- 6x 10kΩ resistors (button pull-ups)
- 2x 180kΩ resistors (battery divider)
- 1x 100Ω resistor (IR LED series)
- 6x tactile push buttons

### For RF Features
- 1x CC1101 module OR NRF24L01+ module
- 1x 10µF capacitor (NRF24 decoupling)
- 2x 10µF capacitors (general decoupling)

### For RFID
- 1x PN532 module (I2C or SPI)

### Optional
- 1x microSD card adapter
- 1x GPS module (serial)
- 1x IR receiver 38kHz
- 1x IR LED 940nm

## Voltage Levels

All GPIO pins operate at **3.3V**. Do not connect 5V signals directly.

**Level Shifting**: If using 5V modules, use a logic level converter.

## Power Supply Considerations

- **USB Power**: Sufficient for basic operation
- **Battery Power**: Use 1S LiPo (3.7V nominal, 4.2V max)
- **RF Modules**: May require external power supply during transmission
- **Current Draw**: ~200mA idle, up to 500mA with RF + display

## Testing Connections

### Using Arduino IDE Serial Monitor
```cpp
// Test I2C devices
Wire.begin(21, 22);
Wire.beginTransmission(0x3C);
if (Wire.endTransmission() == 0) {
  Serial.println("OLED found!");
}
```

### Using esptool.py
```bash
# Read module information
espefuse.py --port /dev/ttyUSB0 summary

# Read flash
esptool.py --port /dev/ttyUSB0 read_flash 0 1000 flash.bin
```

## Troubleshooting

### I2C Not Working
- Check pull-up resistors (typically 4.7kΩ - 10kΩ)
- Verify SDA/SCL connections
- Check for short circuits
- Use `I2C Scanner` example to detect devices

### SPI Not Working
- Verify CS pin is pulled high when inactive
- Check MOSI/MISO/SCK connections
- Add 0.1µF capacitors near module VCC
- Reduce SPI clock speed if having issues

### RF Module Not Detected
- Check power supply voltage (should be 3.3V)
- Verify all SPI connections
- Check CS pin is connected and working
- Add decoupling capacitors
- Try reducing SPI clock speed

## References

- [ESP32 Pinout Reference](https://randomnerdtutorials.com/esp32-pinout-reference-diagrams/)
- [CC1101 Datasheet](https://www.ti.com/product/CC1101)
- [NRF24L01 Datasheet](https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf)
- [PN532 Datasheet](https://www.nxp.com/documents/short_data_sheet/PN532_SDS.pdf)
