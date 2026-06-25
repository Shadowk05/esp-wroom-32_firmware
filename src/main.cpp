#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

// Display library (uncomment one based on your OLED library)
// #include <U8g2lib.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Pin definitions from board config
#include "../boards/ideaspark-esp32/pins_arduino.h"

// Display object for 128x64 OLED
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Forward declarations
void setupDisplay();
void setupRF();
void setupButtons();
void updateDisplay();
void handleButtons();

void setup() {
    // Initialize Serial for debugging
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n");
    Serial.println("========================================");
    Serial.println("Ideaspark ESP32 OLED - Bruce Firmware");
    Serial.println("========================================");
    
    // Initialize I2C for OLED
    Wire.begin(OLED_SDA, OLED_SCL);
    Wire.setClock(400000);
    
    // Setup GPIO pins
    Serial.println("[*] Setting up GPIO pins...");
    pinMode(UP_BTN, INPUT);
    pinMode(DOWN_BTN, INPUT);
    pinMode(LEFT_BTN, INPUT);
    pinMode(RIGHT_BTN, INPUT);
    pinMode(SEL_BTN, INPUT);
    pinMode(ESC_BTN, INPUT);
    
    // Setup RF module CS pins
    pinMode(CC1101_CS, OUTPUT);
    pinMode(NRF24_CS, OUTPUT);
    pinMode(NRF24_CE, OUTPUT);
    pinMode(SDCARD_CS, OUTPUT);
    
    digitalWrite(CC1101_CS, HIGH);
    digitalWrite(NRF24_CS, HIGH);
    digitalWrite(NRF24_CE, LOW);
    digitalWrite(SDCARD_CS, HIGH);
    
    // Setup IR pins
    pinMode(IR_TX_PIN, OUTPUT);
    pinMode(IR_RX_PIN, INPUT);
    digitalWrite(IR_TX_PIN, LOW);
    
    // Setup battery ADC
    pinMode(BAT_PIN, INPUT);
    analogSetAttenuation(ADC_11db);
    
    Serial.println("[+] GPIO setup complete");
    
    // Initialize OLED display
    Serial.println("[*] Initializing OLED display...");
    setupDisplay();
    
    // Initialize RF module
    Serial.println("[*] Initializing RF module...");
    setupRF();
    
    // Initialize buttons
    Serial.println("[*] Setting up buttons...");
    setupButtons();
    
    Serial.println("[+] Initialization complete!");
    delay(2000);
}

void loop() {
    handleButtons();
    updateDisplay();
    delay(100);
}

void setupDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("[-] SSD1306 allocation failed");
        while (1);
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Ideaspark ESP32");
    display.println("OLED");
    display.println("");
    display.println("Initializing...");
    display.display();
    
    Serial.println("[+] OLED initialized successfully");
}

void setupRF() {
    // Initialize SPI for RF modules
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    SPI.setFrequency(1000000);  // 1MHz
    
    Serial.println("[+] SPI initialized for RF modules");
    Serial.println("[*] CC1101 ready on CS=GPIO5");
    Serial.println("[*] NRF24 ready on CS=GPIO17");
}

void setupButtons() {
    Serial.println("[+] Buttons configured");
    Serial.println("    UP:GPIO34, DOWN:GPIO35, LEFT:GPIO32, RIGHT:GPIO33");
    Serial.println("    SELECT:GPIO27, ESC:GPIO14");
}

void handleButtons() {
    if (digitalRead(UP_BTN) == LOW) {
        Serial.println("[BUTTON] UP pressed");
        delay(200);
    }
    if (digitalRead(DOWN_BTN) == LOW) {
        Serial.println("[BUTTON] DOWN pressed");
        delay(200);
    }
    if (digitalRead(LEFT_BTN) == LOW) {
        Serial.println("[BUTTON] LEFT pressed");
        delay(200);
    }
    if (digitalRead(RIGHT_BTN) == LOW) {
        Serial.println("[BUTTON] RIGHT pressed");
        delay(200);
    }
    if (digitalRead(SEL_BTN) == LOW) {
        Serial.println("[BUTTON] SELECT pressed");
        delay(200);
    }
    if (digitalRead(ESC_BTN) == LOW) {
        Serial.println("[BUTTON] ESC pressed");
        delay(200);
    }
}

void updateDisplay() {
    static unsigned long lastUpdate = 0;
    unsigned long now = millis();
    
    // Update display every 500ms
    if (now - lastUpdate < 500) {
        return;
    }
    lastUpdate = now;
    
    // Read battery voltage
    int rawBattery = analogRead(BAT_PIN);
    float voltage = rawBattery * (3.3 / 4095.0);
    int batteryPercent = (voltage - 3.0) * 100 / (4.2 - 3.0);
    if (batteryPercent < 0) batteryPercent = 0;
    if (batteryPercent > 100) batteryPercent = 100;
    
    // Clear and redraw display
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("BRUCE");
    
    display.setTextSize(1);
    display.println("Ideaspark ESP32");
    display.println("");
    
    // Display battery
    display.print("Battery: ");
    display.print(batteryPercent);
    display.println("%");
    
    // Display voltage
    display.print("Voltage: ");
    display.print(voltage, 2);
    display.println("V");
    
    // Display IP or status
    display.println("");
    display.println("Ready for attack!");
    
    display.display();
}
