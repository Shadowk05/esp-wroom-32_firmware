#include <WiFi.h>
#include <Arduino.h>

// WiFi attack functions placeholder

void initWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.println("[+] WiFi initialized in STA mode");
}

void startWiFiScan() {
    Serial.println("[*] Starting WiFi scan...");
    int n = WiFi.scanNetworks();
    Serial.printf("[+] Found %d networks\n", n);
    
    for (int i = 0; i < n; i++) {
        Serial.printf("  %d: %s (RSSI: %d)\n", i+1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }
}
