# Release Notes - RDWC Auto-Doser T4 v1.0.0

## 🚀 Initial Release

We are proud to present the first stable version of the **RDWC Auto-Doser T4**, an open-source hydroponic controller designed for the LILYGO T4 (ESP32) platform.

### ✨ Key Features
*   **Fully Automated Dosing:** PID-like logic for pH regulation and nutrient dosing.
*   **Hardware Support:**
    *   **Display:** LILYGO T4 v1.3 (ILI9341 2.2" TFT).
    *   **Sensors:** Analog pH & EC, DS18B20 Temp, HC-SR04 Level.
    *   **Actuators:** 4-Channel Relay support for 12V Peristaltic Pumps.
*   **Connectivity:**
    *   WiFi Station Mode.
    *   Embedded Web Server (Dashboard).
*   **Stability:**
    *   Generic Analog-to-Value conversion logic (No dependency hell!).
    *   FreeRTOS Multitasking implementation.

### 📦 Known Issues / Limitations
*   **Calibration:** Currently requires editing constants in `config.h` or `Sensors.cpp`. A runtime calibration menu is planned for v1.1.
*   **Web Interface:** Basic status display only. Configuration via web is planned for v1.2.

### 🛠 Installation
1.  Clone this repository.
2.  Open `firmware` in VS Code with PlatformIO.
3.  Edit `src/modules/AppWebServer.cpp` to set your WiFi credentials.
4.  Build and Upload!

---
*Happy Growing! 🌿*
