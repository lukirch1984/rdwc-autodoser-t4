#include "StorageManager.h"

StorageManager::StorageManager() {
    // Use HSPI for SD Card (VSPI is used by Display)
    _spi = new SPIClass(HSPI);
}

bool StorageManager::begin() {
    Serial.println("[Storage] Initializing SD Card...");
    
    // Init SPI bus for SD
    _spi->begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);

    if (!SD.begin(SD_CS, *_spi)) {
        Serial.println("[Storage] Card Mount Failed");
        _sdReady = false;
        return false;
    }

    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("[Storage] No SD card attached");
        _sdReady = false;
        return false;
    }

    Serial.println("[Storage] SD Card initialized.");
    _sdReady = true;

    // Check if log file exists, if not create header
    if (!SD.exists(LOG_FILENAME)) {
        appendFile(LOG_FILENAME, "Time,pH,EC,Temp,Level\n");
    }

    return true;
}

void StorageManager::update(SensorData data) {
    if (!_sdReady) return;

    if (millis() - _lastLogTime >= LOG_INTERVAL_MS) {
        logData(data);
        _lastLogTime = millis();
    }
}

void StorageManager::logData(SensorData data) {
    if (!_sdReady) return;

    // Format: Time(ms),pH,EC,Temp,Level
    // Note: Ideally we would use NTP time here, but millis() is okay for relative duration analysis
    String logEntry = String(millis()) + "," + 
                      String(data.ph, 2) + "," + 
                      String(data.ec, 2) + "," + 
                      String(data.temp, 1) + "," + 
                      String(data.waterLevel, 1) + "\n";

    appendFile(LOG_FILENAME, logEntry.c_str());
    Serial.print("[Storage] Logged: ");
    Serial.print(logEntry);
}

void StorageManager::appendFile(const char* path, const char* message) {
    File file = SD.open(path, FILE_APPEND);
    if (!file) {
        Serial.println("[Storage] Failed to open file for appending");
        return;
    }
    if (!file.print(message)) {
        Serial.println("[Storage] Append failed");
    }
    file.close();
}
