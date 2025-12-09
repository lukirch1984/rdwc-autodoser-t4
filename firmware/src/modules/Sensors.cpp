#include "Sensors.h"
#include <Arduino.h>
#include "../config.h"
#include "../data_types.h"

// For DS18B20 Temperature Sensor
#include <OneWire.h>
#include <DallasTemperature.h>

// For HC-SR04 Ultrasonic Sensor
#define SOUND_SPEED 0.034 // speed of sound in cm/microsecond

// Sensor Objects
OneWire oneWire(PIN_TEMP_SENSOR);
DallasTemperature sensors(&oneWire);

// DFRobot_PH ph; // Removed due to dependency issues
// DFRobot_EC ec; // Removed due to dependency issues

SensorData currentData = {0.0, 0.0, 0.0, 0.0};

// Placeholder functions for pH and EC conversion
float convertAnalogToPH(int analogValue, float temperature) {
    // Convert analog value to voltage first (assuming a voltage divider on the pH probe)
    float voltage = analogValue * (ADC_VREF / ADC_MAX_VALUE); // Voltage reading at the ADC pin

    // Generic linear conversion: pH = pH_at_midpoint + (voltage - voltage_at_midpoint) / slope
    // For many probes, pH 7.0 is around 1.5V. Let's adjust PH_ANALOG_MID_POINT to be consistent with voltage.
    // Assuming PH_ANALOG_MID_POINT is already voltage * (4095/Vref)
    float phValue = 7.0 + ((float)analogValue - PH_ANALOG_MID_POINT) / PH_ANALOG_SLOPE;

    // Basic bounds check
    if (phValue < 0.0) phValue = 0.0;
    if (phValue > 14.0) phValue = 14.0;
    return phValue;
}

float convertAnalogToEC(int analogValue, float temperature) {
    // Convert analog value to voltage
    float voltage = analogValue * (ADC_VREF / ADC_MAX_VALUE);

    // Simple linear scaling: EC = (voltage / voltage_at_high_point) * known_high_value
    // Convert EC_ANALOG_HIGH_POINT (analog value) to voltage first for consistency
    float voltageAtHighPoint = EC_ANALOG_HIGH_POINT * (ADC_VREF / ADC_MAX_VALUE);
    float ecValue = (voltage / voltageAtHighPoint) * EC_KNOWN_HIGH_VALUE;

    // Apply temperature compensation (e.g., to 25C)
    // EC_25C = EC_raw / (1 + EC_TEMP_COMP_FACTOR * (Temperature_C - 25.0))
    if (temperature > 0) { // Avoid division by zero or nonsensical temps
        ecValue = ecValue / (1.0 + EC_TEMP_COMP_FACTOR * (temperature - 25.0));
    }
    
    // Basic bounds check
    if (ecValue < 0.0) ecValue = 0.0;
    return ecValue;
}

void Sensors::init() {
    Serial.println("Sensors initializing...");

    // Initialize DS18B20
    sensors.begin();
    Serial.println("DS18B20 Temperature Sensor initialized.");

    // Initialize HC-SR04
    pinMode(PIN_US_TRIGGER, OUTPUT);
    pinMode(PIN_US_ECHO, INPUT);
    Serial.println("HC-SR04 Ultrasonic Sensor initialized.");

    Serial.println("pH and EC sensor functionality integrated with placeholders.");

    Serial.println("Sensors initialized.");
}

void Sensors::update() {
    // --- Read DS18B20 Temperature ---
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0); // Assuming one sensor
    if (tempC != DEVICE_DISCONNECTED_C) {
        currentData.temp = tempC;
    } else {
        Serial.println("Error: DS18B20 disconnected or invalid reading.");
    }

    // --- Read HC-SR04 Ultrasonic Sensor (Water Level) ---
    digitalWrite(PIN_US_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_US_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_US_TRIGGER, LOW);

    long duration = pulseIn(PIN_US_ECHO, HIGH);
    float distanceCm = duration * SOUND_SPEED / 2;

    // Convert distance to water level. Assumes a known height of the sensor above water.
    // Placeholder: 20cm total depth, sensor at 25cm from bottom.
    float containerHeight = 25.0; // Example: distance from sensor to bottom of container
    if (distanceCm >= containerHeight || distanceCm <= 0) { // Out of range
        currentData.waterLevel = 0.0; // Indicates empty or error
    } else {
        currentData.waterLevel = containerHeight - distanceCm; // Water level in cm
    }
    
    // --- Read pH Sensor ---
    // Replaced DFRobot library call with placeholder
    currentData.ph = convertAnalogToPH(analogRead(PIN_PH_SENSOR), currentData.temp);

    // --- Read EC Sensor ---
    // Replaced DFRobot library call with placeholder
    currentData.ec = convertAnalogToEC(analogRead(PIN_EC_SENSOR), currentData.temp);

    Serial.printf("Sensor Data: pH=%.2f, EC=%.2f, Temp=%.2fC, Level=%.2fcm\n", 
                  currentData.ph, currentData.ec, currentData.temp, currentData.waterLevel);
}

SensorData Sensors::getData() {
    return currentData;
}
