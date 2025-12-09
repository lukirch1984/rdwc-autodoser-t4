# Usage Guide

## System Startup
1.  Ensure all sensors are submerged.
2.  Power on the 12V PSU.
3.  The Display will show a boot screen and perform a **Relay Self-Test** (clicking sound).
4.  Once "READY" appears, the main dashboard loads.

## Calibration (Persistent)
Calibration values for pH and EC, along with dosing targets, are now **persisted** in the ESP32's Flash memory (NVS) using the `ConfigManager`. This means values will survive restarts.

*   **Current Method:** For now, you must adjust calibration values (e.g., `phMidpointVolt`, `ecKFactor`) directly in `src/drivers/ConfigManager.cpp` and re-upload the firmware to set new defaults.
*   **Future:** A runtime calibration menu via the UI or web interface is planned.

## Safety Features (Fail-Safe Dosing)
The `DosingManager` implements several fail-safe mechanisms:
*   **Plausibility Check:** Dosing is halted if sensor readings (pH, EC) are outside realistic bounds.
*   **Pump Timeout:** A single pump will not run for more than `DOSING_TIMEOUT_MS` (10 seconds) at a time.
*   **Cooldown:** After any dosing event, the system waits for `DOSING_COOLDOWN_MS` (15 minutes) to allow the solution to mix before another dose.

## Data Logging (SD Card)
Sensor data (pH, EC, Temperature, Water Level) is logged to a `datalog.csv` file on the SD card every `LOG_INTERVAL_MS` (5 minutes).
*   **File Format:** CSV (`Time,pH,EC,Temp,Level`)
*   **Access:** Eject the SD card and read it on a computer.

## MQTT Connectivity
The `NetworkManager` handles WiFi and MQTT connections.
*   **Configuration:** Set your WiFi SSID, password, and MQTT broker details in `src/drivers/NetworkManager.h`.
*   **Data Format:** Sensor data is published as a JSON string to the `rdwc/status` topic every 10 seconds.
*   **Example Topic:** `rdwc/status`
*   **Example Payload:** `{"ph":6.12, "ec":1.35, "temp":22.8, "level":15.3}`

## Web Interface (Future)
The legacy web interface has been disabled in favor of MQTT. A more robust and configurable web interface is planned for future releases.