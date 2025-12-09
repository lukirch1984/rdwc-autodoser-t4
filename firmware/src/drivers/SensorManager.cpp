#include "SensorManager.h"

// Hardware Constraints (from Master Context)
// ADS1115 Address: 0x48 (Addr pin to GND)

SensorData _currentData = {0.0, 0.0, 0.0, 0.0};

SensorManager::SensorManager(uint8_t tempPin, uint8_t trigPin, uint8_t echoPin) {
    _tempPin = tempPin;
    _trigPin = trigPin;
    _echoPin = echoPin;

    _oneWire = new OneWire(_tempPin);
    _sensors = new DallasTemperature(_oneWire);
}

bool SensorManager::begin() {
    bool success = true;
    Serial.println("[Sensors] Initializing...");

    // 1. Init ADS1115
    if (!_ads.begin()) {
        Serial.println("[Sensors] ERROR: ADS1115 not found at 0x48!");
        success = false;
        _adsReady = false;
    } else {
        Serial.println("[Sensors] ADS1115 connected.");
        _adsReady = true;
        // Set Gain. 
        // GAIN_ONE: +/- 4.096V range (1 bit = 0.125mV)
        // Check your sensor output! If 5V sensor, use GAIN_TWOTHIRDS (+/- 6.144V)
        _ads.setGain(GAIN_TWOTHIRDS); 
    }

    // 2. Init Temp
    _sensors->begin();
    
    // 3. Init Ultrasonic
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);

    return success;
}

float SensorManager::readADSVoltage(uint8_t channel) {
    if (!_adsReady) return 0.0;
    
    int16_t adc = _ads.readADC_SingleEnded(channel);
    // With GAIN_TWOTHIRDS, 1 bit = 0.1875mV
    float volts = adc * 0.0001875;
    return volts;
}

void SensorManager::update() {
    // --- 1. Temperature ---
    _sensors->requestTemperatures();
    float t = _sensors->getTempCByIndex(0);
    if (t > -127.0) _currentData.temp = t;

    // --- 2. Ultrasonic Level ---
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    
    long duration = pulseIn(_echoPin, HIGH, 30000); // 30ms timeout
    if (duration > 0) {
        // Sound speed 0.034 cm/us
        _currentData.waterLevel = duration * 0.034 / 2;
    } else {
        _currentData.waterLevel = -1.0; // Error
    }

    // --- 3. pH (ADS Channel 0) ---
    float phVolt = readADSVoltage(0);
    // Generic Linear: pH 7.0 @ 2.5V (Adjust as needed)
    // Formula: pH = 7 + ((2.5 - Voltage) / Slope)
    // Let's assume a slope of 0.18V per pH unit
    _currentData.ph = 7.0 + ((2.5 - phVolt) / 0.18);

    // --- 4. EC (ADS Channel 1) ---
    float ecVolt = readADSVoltage(1);
    // Simple placeholder logic: 1V = 1.0 mS/cm
    _currentData.ec = ecVolt * 1.0; 
}

SensorData SensorManager::getData() {
    return _currentData;
}
