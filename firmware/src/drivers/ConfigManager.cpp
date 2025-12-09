#include "ConfigManager.h"

ConfigManager::ConfigManager() {
    // Defaults (Safe values)
    phMidpointVolt = 2.50;
    phSlopeVolt = 0.18;
    ecKFactor = 1.0;
    targetPh = 6.0;
    targetEc = 1.2;
}

void ConfigManager::begin() {
    _prefs.begin(_ns, false); // Read-Write mode

    // Load values (with defaults if missing)
    phMidpointVolt = _prefs.getFloat("ph_mid", 2.50);
    phSlopeVolt = _prefs.getFloat("ph_slope", 0.18);
    ecKFactor = _prefs.getFloat("ec_k", 1.0);
    
    targetPh = _prefs.getFloat("target_ph", 6.0);
    targetEc = _prefs.getFloat("target_ec", 1.2);

    Serial.println("[Config] Loaded configuration from NVS.");
    Serial.printf("pH Mid: %.2fV, Slope: %.2fV\n", phMidpointVolt, phSlopeVolt);
}

void ConfigManager::savePhCalibration(float midpoint, float slope) {
    _prefs.putFloat("ph_mid", midpoint);
    _prefs.putFloat("ph_slope", slope);
    phMidpointVolt = midpoint;
    phSlopeVolt = slope;
    Serial.println("[Config] pH Calibration saved.");
}

void ConfigManager::saveEcCalibration(float kFactor) {
    _prefs.putFloat("ec_k", kFactor);
    ecKFactor = kFactor;
    Serial.println("[Config] EC Calibration saved.");
}

void ConfigManager::saveTargets(float ph, float ec) {
    _prefs.putFloat("target_ph", ph);
    _prefs.putFloat("target_ec", ec);
    targetPh = ph;
    targetEc = ec;
    Serial.println("[Config] Targets saved.");
}

void ConfigManager::resetDefaults() {
    _prefs.clear();
    // Reset local vars
    phMidpointVolt = 2.50;
    phSlopeVolt = 0.18;
    ecKFactor = 1.0;
    targetPh = 6.0;
    targetEc = 1.2;
    Serial.println("[Config] Factory reset performed.");
}
