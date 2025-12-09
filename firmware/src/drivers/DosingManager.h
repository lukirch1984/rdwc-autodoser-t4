#pragma once

#include <Arduino.h>
#include "RelayManager.h"
#include "SensorManager.h"

// --- Safety Constants ---
#define SAFE_PH_MIN 4.0
#define SAFE_PH_MAX 9.0
#define SAFE_EC_MIN 0.1 // Prevent dosing in fresh water/air

// --- Timing Constants ---
#define DOSING_TIMEOUT_MS 10000  // Max pump runtime per event (10s)
#define DOSING_COOLDOWN_MS 900000 // Wait 15 mins between events (mixing time)

class DosingManager {
private:
    RelayManager* _relays;
    
    // State Tracking
    unsigned long _lastDoseTime = 0;
    bool _isDosing = false;
    uint8_t _activePumpIndex = 255; // 255 = None
    unsigned long _doseStartTime = 0;

    // Target Values (Default)
    float _targetPH = 6.0;
    float _targetEC = 1.2;

    bool isSensorValueSafe(float ph, float ec);

public:
    DosingManager(RelayManager* relayMgr);
    void begin();
    
    // Main Logic loop (call frequently)
    void update(SensorData currentSensors);

    // Configuration
    void setTargets(float ph, float ec);
    
    // Emergency Stop
    void emergencyStop();
};
