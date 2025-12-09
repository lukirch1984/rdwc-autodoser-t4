#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

// Drivers
#include "drivers/RelayManager.h"
#include "drivers/SensorManager.h"
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

    // 3. Initialize Relays
    if (!relays.begin()) {
        display.showStatus("RELAY ERR", TFT_RED);
        Serial.println("ERROR: Relay (PCF8574) fail!");
    } else {
        Serial.println("OK: Relay Controller");
    }

    // 4. Initialize Sensors
    if (!sensors.begin()) {
        display.showStatus("SENS ERR", TFT_ORANGE);
        Serial.println("WARN: ADS1115 missing");
    } else {
        Serial.println("OK: Sensors");
    }

    display.showStatus("READY", TFT_GREEN);
}

void loop() {
    // 1. Update Sensors
    sensors.update();
    SensorData data = sensors.getData();

    // 2. Update UI
    display.updateSensorValues(data);

    delay(200); // Higher refresh rate possible now due to optimized drawing
}