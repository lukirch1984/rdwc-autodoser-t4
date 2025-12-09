#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

// Drivers
#include "drivers/RelayManager.h"
#include "drivers/SensorManager.h"
#include "drivers/DosingManager.h"
#include "drivers/ConfigManager.h"
#include "drivers/StorageManager.h"
#include "drivers/NetworkManager.h" // Include NetworkManager
// #include "modules/AppWebServer.h" // Disabled for MQTT focus
#include "ui/DisplayManager.h"

// --- Configuration ---
#define I2C_SDA 21
#define I2C_SCL 22

// Sensor Pins
#define PIN_TEMP 25
#define PIN_TRIG 26
#define PIN_ECHO 39

// --- Objects ---
RelayManager relays(0x20); // PCF8574 Address
SensorManager sensors(PIN_TEMP, PIN_TRIG, PIN_ECHO);
DosingManager dosing(&relays);
ConfigManager config;
StorageManager storage;
NetworkManager network; // Network Instance
DisplayManager display;

void setup() {
    Serial.begin(115200);
    Serial.println("\n\nRDWC Auto-Doser T4 - Booting...");

    // 1. Initialize I2C Bus
    Wire.begin(I2C_SDA, I2C_SCL);
    
    // 2. Initialize UI
    display.begin();
    display.drawInterface();
    display.showStatus("BOOTING...", TFT_YELLOW);

    // 3. Initialize Config (Load values)
    config.begin();

    // 4. Initialize Relays
    if (!relays.begin()) {
        display.showStatus("RELAY ERR", TFT_RED);
        Serial.println("ERROR: Relay (PCF8574) fail!");
    } else {
        Serial.println("OK: Relay Controller");
    }

    // 5. Initialize Sensors
    if (!sensors.begin()) {
        display.showStatus("SENS ERR", TFT_ORANGE);
        Serial.println("WARN: ADS1115 missing");
    } else {
        Serial.println("OK: Sensors");
    }
    sensors.setCalibration(config.phMidpointVolt, config.phSlopeVolt, config.ecKFactor);

    // 6. Initialize Storage
    if (!storage.begin()) {
        display.showStatus("NO SD CARD", TFT_ORANGE);
        Serial.println("WARN: SD Card init failed");
    } else {
        Serial.println("OK: SD Card");
    }

    // 7. Initialize Network
    network.begin(); // Starts WiFi & MQTT setup

    // 8. Initialize Dosing
    dosing.begin();
    dosing.setTargets(config.targetPh, config.targetEc);

    display.showStatus("READY", TFT_GREEN);
}

void loop() {
    // 1. Update Sensors
    sensors.update();
    SensorData data = sensors.getData();

    // 2. Run Dosing Logic
    dosing.update(data);

    // 3. Log Data (Every 5 mins)
    storage.update(data);

    // 4. Update Network (MQTT)
    network.update(data);

    // 5. Update UI
    display.updateSensorValues(data);

    delay(200);
}