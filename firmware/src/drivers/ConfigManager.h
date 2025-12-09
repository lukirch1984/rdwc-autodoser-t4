#pragma once

#include <Arduino.h>
#include <Preferences.h>

class ConfigManager {
private:
    Preferences _prefs;
    const char* _ns = "rdwc_config"; // Namespace

public:
    // Calibration Values
    float phMidpointVolt;
    float phSlopeVolt;
    float ecKFactor;

    // Dosing Targets
    float targetPh;
    float targetEc;

    ConfigManager();
    void begin();
    
    // Save methods
    void savePhCalibration(float midpoint, float slope);
    void saveEcCalibration(float kFactor);
    void saveTargets(float ph, float ec);
    
    // Factory Reset
    void resetDefaults();
};
