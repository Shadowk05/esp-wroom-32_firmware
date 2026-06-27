#include <Arduino.h>
#include "../boards/ideaspark-esp32/pins_arduino.h"

// Battery monitoring functions

int getBatteryPercentage() {
    int rawValue = analogRead(BAT_PIN);
    float voltage = rawValue * (3.3 / 4095.0);
    
    // LiPo voltage curve: 3.0V = 0%, 4.2V = 100%
    int percent = (voltage - 3.0) * 100 / (4.2 - 3.0);
    
    if (percent < 0) return 0;
    if (percent > 100) return 100;
    
    return percent;
}

float getBatteryVoltage() {
    int rawValue = analogRead(BAT_PIN);
    float voltage = rawValue * (3.3 / 4095.0);
    return voltage;
}

bool isBatteryCritical() {
    return getBatteryPercentage() < 10;
}
