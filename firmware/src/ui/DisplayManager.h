#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "../drivers/SensorManager.h" // Needed for SensorData struct

class DisplayManager {
private:
    TFT_eSPI* _tft;
    
    // Cache old values to minimize redraws
    float _lastPh = -1.0;
    float _lastEc = -1.0;
    float _lastTemp = -1.0;
    float _lastLvl = -1.0;

    void drawLabel(int x, int y, const char* label);
    void drawValue(int x, int y, float value, float lastValue, int decimals, const char* unit);

public:
    DisplayManager();
    void begin();
    
    // Draw static UI elements (grid, labels)
    void drawInterface();
    
    // Update dynamic values
    void updateSensorValues(SensorData data);
    
    // Show Status Messages (e.g., "WiFi Connecting...")
    void showStatus(const char* msg, uint16_t color);
};
