#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <OneWire.h>
#include <DallasTemperature.h>

struct SensorData {
    float ph;
    float ec;
    float temp;
    float waterLevel;
};

class SensorManager {
private:
    // I2C ADC
    Adafruit_ADS1115 _ads;
    bool _adsReady = false;

    // Temperature (OneWire)
    OneWire* _oneWire;
    DallasTemperature* _sensors;
    uint8_t _tempPin;

    // Ultrasonic
    uint8_t _trigPin;
    uint8_t _echoPin;

    // Calibration constants (Defaults)
    const float VOLTAGE_REF = 5.0; // ADS1115 typically powered by 5V in these setups, or 3.3V. Check VDD!
    // Using 5V for dynamic range is common with 5V sensors.
    
    float readADSVoltage(uint8_t channel);

public:
    SensorManager(uint8_t tempPin, uint8_t trigPin, uint8_t echoPin);
    bool begin();
    void update(); // Call this in loop to refresh readings
    
    SensorData getData();
};
