#include "DisplayManager.h"

// Layout Constants
#define CELL_W 160
#define CELL_H 100
#define HEADER_H 30

// Colors
#define C_BG TFT_BLACK
#define C_TEXT TFT_WHITE
#define C_ACCENT TFT_DARKCYAN
#define C_WARN TFT_ORANGE
#define C_ALARM TFT_RED

DisplayManager::DisplayManager() {
    _tft = new TFT_eSPI();
}

void DisplayManager::begin() {
    _tft->init();
    _tft->setRotation(1); // Landscape
    _tft->fillScreen(C_BG);
}

void DisplayManager::drawInterface() {
    _tft->fillScreen(C_BG);
    
    // Header Bar
    _tft->fillRect(0, 0, 320, HEADER_H, C_ACCENT);
    _tft->setTextColor(TFT_WHITE, C_ACCENT);
    _tft->setTextSize(2);
    _tft->setCursor(10, 6);
    _tft->print("RDWC Controller");

    // Grid Lines
    _tft->drawFastVLine(160, HEADER_H, 240-HEADER_H, TFT_DARKGREY);
    _tft->drawFastHLine(0, HEADER_H + CELL_H, 320, TFT_DARKGREY);

    // Labels (Static)
    drawLabel(10, HEADER_H + 10, "pH Value");
    drawLabel(170, HEADER_H + 10, "EC (mS/cm)");
    drawLabel(10, HEADER_H + CELL_H + 10, "Water Temp");
    drawLabel(170, HEADER_H + CELL_H + 10, "Level (cm)");
}

void DisplayManager::drawLabel(int x, int y, const char* label) {
    _tft->setTextColor(TFT_LIGHTGREY, C_BG); // Grey text on Black BG
    _tft->setTextSize(1);
    _tft->setCursor(x, y);
    _tft->print(label);
}

void DisplayManager::drawValue(int x, int y, float value, float lastValue, int decimals, const char* unit) {
    // Only redraw if changed significantly
    if (abs(value - lastValue) < 0.01) return;

    // Clear previous area (approximated)
    // Or simpler: Use setTextColor(FG, BG) which overwrites background
    _tft->setTextColor(TFT_WHITE, C_BG); 
    
    // Font 4 is a nice medium font
    // _tft->setTextFont(4); 
    // But sticking to standard GFX font for compatibility first, scaled up
    _tft->setTextSize(3); 
    _tft->setCursor(x, y);
    
    _tft->print(value, decimals);
    
    // Unit (smaller)
    _tft->setTextSize(1);
    _tft->print(" ");
    _tft->print(unit);
}

void DisplayManager::updateSensorValues(SensorData data) {
    // Top-Left: pH
    drawValue(10, HEADER_H + 30, data.ph, _lastPh, 2, "");
    _lastPh = data.ph;

    // Top-Right: EC
    drawValue(170, HEADER_H + 30, data.ec, _lastEc, 2, "mS");
    _lastEc = data.ec;

    // Bottom-Left: Temp
    drawValue(10, HEADER_H + CELL_H + 30, data.temp, _lastTemp, 1, "C");
    _lastTemp = data.temp;

    // Bottom-Right: Level
    drawValue(170, HEADER_H + CELL_H + 30, data.waterLevel, _lastLvl, 0, "cm");
    _lastLvl = data.waterLevel;
}

void DisplayManager::showStatus(const char* msg, uint16_t color) {
    // Draw in the top right of header
    // Simple implementation: Just overwrite a status area
    _tft->fillRect(200, 0, 120, HEADER_H, C_ACCENT); // Clear
    
    _tft->setTextColor(color, C_ACCENT);
    _tft->setTextSize(1);
    _tft->setCursor(210, 10);
    _tft->print(msg);
}
