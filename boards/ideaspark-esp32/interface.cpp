#include "core/powerSave.h"
#include <Wire.h>

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description: Initial setup for the Ideaspark ESP-WROOM-32 OLED board
***************************************************************************************/

void _setup_gpio() {
    // Configure button pins as inputs
    pinMode(UP_BTN, INPUT);
    pinMode(DOWN_BTN, INPUT);
    pinMode(LEFT_BTN, INPUT);
    pinMode(RIGHT_BTN, INPUT);
    pinMode(SEL_BTN, INPUT);
    pinMode(ESC_BTN, INPUT);

    // Configure RF module CS pins as outputs
    pinMode(CC1101_CS, OUTPUT);
    pinMode(NRF24_CS, OUTPUT);
    pinMode(NRF24_CE, OUTPUT);
    pinMode(SDCARD_CS, OUTPUT);
    
    // Set CS pins high (inactive state)
    digitalWrite(CC1101_CS, HIGH);
    digitalWrite(NRF24_CS, HIGH);
    digitalWrite(NRF24_CE, LOW);
    digitalWrite(SDCARD_CS, HIGH);

    // Configure IR pins
    pinMode(IR_TX_PIN, OUTPUT);
    pinMode(IR_RX_PIN, INPUT);
    digitalWrite(IR_TX_PIN, LOW);

    // Configure battery ADC pin
    pinMode(BAT_PIN, INPUT);
    analogSetAttenuation(ADC_11db);

    // Initialize I2C for OLED display
    Wire.begin(OLED_SDA, OLED_SCL);
    Wire.setClock(400000);  // 400kHz I2C speed

    // Set default RF module
    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
    bruceConfigPins.irRx = IR_RX_PIN;
    bruceConfigPins.irTx = IR_TX_PIN;
}

/*********************************************************************
** Function: setBrightness
** Description: Set OLED brightness (0-100)
** Note: OLED brightness is controlled via software in display library
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    // For OLED displays, brightness is controlled through the display library
    // This is typically handled by adjusting the contrast register
    // Implementation depends on the OLED library used (U8g2, Adafruit, etc.)
    // Placeholder for OLED brightness adjustment
    if (brightval == 0) {
        // Turn off display
    } else {
        // Set brightness level (converted from 0-100 to appropriate range)
    }
}

/*********************************************************************
** Function: isCharging
** Description: Determine if device is charging
** Note: Ideaspark board may not have charge detection
**********************************************************************/
bool isCharging() {
    // This board likely doesn't have built-in charge detection
    // Return false or implement if using external power management IC
    return false;
}

/*********************************************************************
** Function: getBattery
** Description: Get battery level as percentage (0-100)
** Note: Uses ADC pin 36 for voltage reading
**********************************************************************/
int getBattery() {
    // Read ADC value from battery pin
    int rawValue = analogRead(BAT_PIN);
    
    // Convert ADC reading to voltage (assuming voltage divider)
    // ADC range: 0-4095 corresponds to 0-3.3V
    float voltage = rawValue * (3.3 / 4095.0);
    
    // Convert voltage to percentage (typical LiPo: 3.0V = 0%, 4.2V = 100%)
    int percent = (voltage - 3.0) * 100 / (4.2 - 3.0);
    
    if (percent < 0) return 0;
    if (percent > 100) return 100;
    
    return percent;
}

/*********************************************************************
** Function: setDisplay
** Description: Initialize and configure the OLED display
** Note: Call this during setup to initialize display
**********************************************************************/
void _initDisplay() {
    // OLED initialization code
    // This depends on which OLED library is being used
    // Common options: U8g2, Adafruit SSD1306, etc.
    // 
    // Example for common 0.96" OLED 128x64:
    // - I2C address: 0x3C
    // - SDA: GPIO 21
    // - SCL: GPIO 22
}
