#include "Dosing.h"
#include <Arduino.h>
#include "../config.h"
#include "Sensors.h" // To get sensor data
#include "../data_types.h" // Include common data types

// Define the state of the relays. HIGH is OFF, LOW is ON (common for many relay boards)
#define RELAY_ON  LOW
#define RELAY_OFF HIGH

// Dosing Timers (to prevent continuous dosing and allow mixing)
const unsigned long DOSING_INTERVAL_MS = 30000; // 30 seconds between dosing attempts
const unsigned long DOSING_DURATION_MS = 500;   // 0.5 seconds dosing pulse
static unsigned long lastDoseTime = 0; // Declared as static to persist across calls

void Dosing::init() {
    pinMode(PIN_RELAY_PH_DOWN, OUTPUT);
    pinMode(PIN_RELAY_PH_UP, OUTPUT);
    pinMode(PIN_RELAY_NUT_A, OUTPUT);
    pinMode(PIN_RELAY_NUT_B, OUTPUT);
    
    // Ensure all relays are OFF initially
    digitalWrite(PIN_RELAY_PH_DOWN, RELAY_OFF);
    digitalWrite(PIN_RELAY_PH_UP, RELAY_OFF);
    digitalWrite(PIN_RELAY_NUT_A, RELAY_OFF);
    digitalWrite(PIN_RELAY_NUT_B, RELAY_OFF);

    Serial.println("Dosing system initialized.");
}

void Dosing::update() {
    unsigned long currentTime = millis();
    // Use fully qualified name for SensorData to be explicit, though it should be global
    SensorData data = Sensors::getData(); // Get current sensor readings

    if (currentTime - lastDoseTime >= DOSING_INTERVAL_MS) {
        lastDoseTime = currentTime; // Reset timer for next cycle

        // --- pH Dosing Logic ---
        if (data.ph < TARGET_PH_MIN) {
            Serial.println("pH too low, adding pH Up...");
            digitalWrite(PIN_RELAY_PH_UP, RELAY_ON);
            delay(DOSING_DURATION_MS);
            digitalWrite(PIN_RELAY_PH_UP, RELAY_OFF);
        } else if (data.ph > TARGET_PH_MAX) {
            Serial.println("pH too high, adding pH Down...");
            digitalWrite(PIN_RELAY_PH_DOWN, RELAY_ON);
            delay(DOSING_DURATION_MS);
            digitalWrite(PIN_RELAY_PH_DOWN, RELAY_OFF);
        }

        // --- EC Dosing Logic ---
        if (data.ec < TARGET_EC_MIN) {
            Serial.println("EC too low, adding Nutrients A & B...");
            // Dosing Nutrients A and B simultaneously for simplicity, or add separate logic
            digitalWrite(PIN_RELAY_NUT_A, RELAY_ON);
            digitalWrite(PIN_RELAY_NUT_B, RELAY_ON);
            delay(DOSING_DURATION_MS);
            digitalWrite(PIN_RELAY_NUT_A, RELAY_OFF);
            digitalWrite(PIN_RELAY_NUT_B, RELAY_OFF);
        }
        // Optional: Implement a check for EC_MAX to prevent over-dosing, maybe an alarm.
    }
}

