#include "DosingManager.h"

DosingManager::DosingManager(RelayManager* relayMgr) {
    _relays = relayMgr;
}

void DosingManager::begin() {
    _lastDoseTime = millis() - DOSING_COOLDOWN_MS; // Allow immediate dosing on boot
    Serial.println("[Dosing] Manager initialized. Safety limits active.");
}

void DosingManager::setTargets(float ph, float ec) {
    _targetPH = ph;
    _targetEC = ec;
}

bool DosingManager::isSensorValueSafe(float ph, float ec) {
    if (ph < SAFE_PH_MIN || ph > SAFE_PH_MAX) {
        Serial.printf("[Dosing] SAFETY STOP: pH %.2f out of safe range (%.1f-%.1f)\n", ph, SAFE_PH_MIN, SAFE_PH_MAX);
        return false;
    }
    if (ec < SAFE_EC_MIN) {
        Serial.printf("[Dosing] SAFETY STOP: EC %.2f too low (Air/Fresh water)\n", ec);
        return false;
    }
    return true;
}

void DosingManager::emergencyStop() {
    _relays->allOff();
    _isDosing = false;
    Serial.println("[Dosing] EMERGENCY STOP TRIGGERED!");
}

void DosingManager::update(SensorData sensors) {
    unsigned long now = millis();

    // 1. Safety Check: If actively dosing, check timeout
    if (_isDosing) {
        if (now - _doseStartTime > DOSING_TIMEOUT_MS) {
            Serial.println("[Dosing] Timeout reached. Stopping pumps.");
            _relays->setRelay(_activePumpIndex, false);
            _isDosing = false;
            _lastDoseTime = now; // Start cooldown
        }
        return; // Don't start new logic while dosing
    }

    // 2. Cooldown Check
    if (now - _lastDoseTime < DOSING_COOLDOWN_MS) {
        return; // Wait for mixing
    }

    // 3. Sensor Plausibility Check
    if (!isSensorValueSafe(sensors.ph, sensors.ec)) {
        return; // Sensors invalid, do nothing
    }

    // 4. Logic Decision Tree
    // Priority: pH > EC
    
    // --- pH Logic ---
    if (sensors.ph > _targetPH + 0.2) {
        // pH too HIGH -> Add pH Down (Pump 0)
        Serial.println("[Dosing] pH High. Dosing pH Down...");
        _activePumpIndex = 0;
        _relays->setRelay(0, true);
        _isDosing = true;
        _doseStartTime = now;
        return;
    } 
    else if (sensors.ph < _targetPH - 0.2) {
        // pH too LOW -> Add pH Up (Pump 1)
        Serial.println("[Dosing] pH Low. Dosing pH Up...");
        _activePumpIndex = 1;
        _relays->setRelay(1, true);
        _isDosing = true;
        _doseStartTime = now;
        return;
    }

    // --- EC Logic ---
    // Only dose nutrients if pH is stable to avoid lockout
    if (sensors.ec < _targetEC - 0.2) {
        // EC too LOW -> Add Nutrients A (Pump 2) AND B (Pump 3)
        // Ideally we alternate or dose together. For simplicity v1.1: Dose A, next cycle Dose B?
        // Or simplified: Just Pump A for now (Demo).
        Serial.println("[Dosing] EC Low. Dosing Nutrients...");
        _activePumpIndex = 2; // Pump A
        _relays->setRelay(2, true);
        _isDosing = true;
        _doseStartTime = now;
        return;
    }
}
