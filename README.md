# RDWC Auto-Doser T4

**Open Source Hydroponic Controller for LILYGO T4 (ESP32)**

![Status](https://img.shields.io/badge/Status-Stable-green)
![License](https://img.shields.io/badge/License-MIT-blue)
![Platform](https://img.shields.io/badge/Platform-ESP32-orange)

The **RDWC Auto-Doser T4** is a professional-grade, DIY controller for Recirculating Deep Water Culture systems. It solves the pin limitation of the LILYGO T4 display board by utilizing an I2C-centric architecture for unlimited expansion.

## 📚 Documentation
Full documentation is available in the `docs/` folder or via our [GitHub Pages site](https://lukirch1984.github.io/rdwc-autodoser-t4/).

*   [**Wiring Guide**](docs/wiring.md): How to connect the I2C sensors and relays.
*   [**Bill of Materials**](docs/bom.md): What to buy.
*   [**Usage Guide**](docs/usage.md): How to operate and calibrate.
*   [**Contributing**](docs/contributing.md): How to help.
*   [**Development Log**](DEVELOPMENT_LOG.md): Track the evolution of the project.

## ✨ Key Features
*   **Precision Sensing:** Uses **ADS1115** (16-bit ADC) for lab-grade pH and EC with **Automatic Temperature Compensation (ATC)**.
*   **Safety & Reliability:** Implements **Fail-Safe** mechanisms (plausibility checks, dose timeouts, cooldowns) to protect your plants.
*   **Usability:** Calibration values and dosing targets are **persistently stored** in Flash memory (NVS).
*   **Data Logging:** Logs sensor data to **SD Card** every 5 minutes for long-term analysis.
*   **IoT Ready:** Sends live sensor data via **MQTT** to a broker (e.g., Home Assistant).
*   **Safe Switching:** Uses **PCF8574** I/O expander to drive relays, protecting the MCU.
*   **Visual Dashboard:** 320x240 Color TFT display (ILI9341).
*   **Remote Monitoring:** (Planned for future releases, currently MQTT is prioritized)

## 🚀 Quick Start
1.  **Hardware:** Assemble the system according to the [Wiring Guide](docs/wiring.md).
2.  **Firmware:**
    *   Open `firmware` in VS Code (PlatformIO).
    *   Edit `src/drivers/NetworkManager.h` with your WiFi and MQTT credentials.
    *   Run `pio run --target upload`.
3.  **Docs:** Run `mkdocs serve` to view the full manual locally.

## ⚠️ Hardware Requirement
This firmware **REQUIRES** an I2C bus with:
*   **PCF8574** (Address 0x20) for Relays.
*   **ADS1115** (Address 0x48) for Sensors.

Direct GPIO connection of sensors is **NOT** supported due to pin conflicts on the T4 board.

---
*License: MIT. Created by the Community.*