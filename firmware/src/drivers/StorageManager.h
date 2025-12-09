#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "SensorManager.h" // For SensorData

// SD Card Pins (LILYGO T4 v1.3 specific)
#define SD_MISO 2
#define SD_MOSI 15
#define SD_SCLK 14
#define SD_CS   13

#define LOG_FILENAME "/datalog.csv"
#define LOG_INTERVAL_MS 300000 // 5 Minutes

class StorageManager {
private:
    SPIClass* _spi;
    bool _sdReady = false;
    unsigned long _lastLogTime = 0;

    void appendFile(const char* path, const char* message);

public:
    StorageManager();
    bool begin();
    
    // Call this in loop to check if it's time to log
    void update(SensorData data);
    
    // Force log entry
    void logData(SensorData data);
};
