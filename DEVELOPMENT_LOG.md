# Development Log - RDWC Auto-Doser T4

This log tracks all architectural changes, feature implementations, and refactoring steps.

## 2025-06-18

### [FEATURE] Phase 5: IoT & MQTT
*   **Time:** 00:25 (approx)
*   **Description:** Replaced basic WebServer with `NetworkManager` for robust MQTT connectivity.
*   **Changes:**
    *   **New Driver:** `NetworkManager` handles WiFi reconnects and MQTT pub/sub.
    *   **Feature:** Publishes sensor data JSON to `rdwc/status` every 10s.
    *   **Cleanup:** Removed legacy `AppWebServer` code to avoid resource conflicts.
*   **Status:** ✅ **PASS** (Compiles successfully)

### [FEATURE] Phase 4: Data Logging
*   **Time:** 00:15 (approx)
*   **Description:** Implemented `StorageManager` to log sensor data to the SD card.
*   **Changes:**
    *   **New Driver:** `StorageManager` handles SPI/SD initialization on HSPI.
    *   **Logic:** Writes CSV format (`Time,pH,EC,Temp,Level`) every 5 minutes.
    *   **Integration:** `main.cpp` checks SD presence and updates log cyclically.
*   **Status:** ✅ **PASS** (Compiles successfully)

### [FEATURE] Phase 3: Usability & Persistence
*   **Time:** 00:05 (approx)
*   **Description:** Implemented `ConfigManager` using ESP32 `Preferences` to store calibration values and targets permanently.
*   **Changes:**
    *   **New Driver:** `ConfigManager` handles NVS storage.
    *   **Logic:** `SensorManager` now accepts dynamic calibration values via `setCalibration()`.
    *   **Logic:** `DosingManager` accepts dynamic targets.
    *   **Integration:** `main.cpp` loads config on boot and applies it to subsystems.
*   **Status:** ✅ **PASS** (Compiles successfully)

### [FEATURE] Phase 2: Precision (ATC)
*   **Time:** 23:55 (approx)
*   **Description:** Added Automatic Temperature Compensation for pH and EC sensors.
*   **Changes:**
    *   **Logic:** pH calculation now uses Nernst equation correction based on live water temperature.
    *   **Logic:** EC calculation now normalizes to 25°C using standard 2%/°C coefficient.
    *   **Safety:** Added fallback temperature (25°C) if temp sensor fails, to prevent math errors.
*   **Status:** ✅ **PASS** (Code integrated)

### [FEATURE] Phase 1: Safety & Dosing Logic
*   **Time:** 23:45 (approx)
*   **Description:** Implemented professional dosing logic with strict safety constraints.
*   **Changes:**
    *   **New Driver:** `DosingManager` class.
    *   **Feature:** `isSensorValueSafe()` prevents dosing if pH/EC are out of realistic bounds.
    *   **Feature:** `DOSING_TIMEOUT_MS` (10s) limits max pump runtime.
    *   **Feature:** `DOSING_COOLDOWN_MS` (15m) enforces mixing time between doses.
    *   **Integration:** `main.cpp` now orchestrates Sensors -> Dosing -> UI.
*   **Status:** ✅ **PASS** (Compiles successfully)

### [REFACTOR] Migration to I2C Architecture
*   **Time:** 23:30 (approx)
*   **Description:** Complete overhaul of the hardware abstraction layer to solve GPIO limitation issues on LILYGO T4.
*   **Changes:**
    *   **Removed:** Direct GPIO control for Relays and Analog Sensors.
    *   **Added:** `RelayManager` (PCF8574 Support).
    *   **Added:** `SensorManager` (ADS1115 Support).
    *   **Added:** `DisplayManager` (Flicker-free UI).
    *   **Config:** Updated `platformio.ini` with new libraries and hardcoded pins.
    *   **Docs:** Created comprehensive dual-language documentation (EN/DE) with `mkdocs-static-i18n`.
*   **Status:** ✅ **PASS** (Compiles successfully, CI/CD pipeline active)

---
*End of Log*