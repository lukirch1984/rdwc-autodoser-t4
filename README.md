# RDWC Auto-Doser T4

**Professional Open Source Hydroponic Controller for LILYGO T4 (ESP32)**

![Status](https://img.shields.io/badge/Status-Development-orange)
![License](https://img.shields.io/badge/License-MIT-green)

The **RDWC Auto-Doser T4** is a fully automated dosing system for Recirculating Deep Water Culture (RDWC) hydroponics. It monitors pH, EC, water temperature, and water level, and automatically doses pH adjusters and nutrients to keep your system in the perfect range.

## 🌟 Features
*   **Central Control:** Based on the powerful **LILYGO T4 v1.3** (ESP32 with 2.2" ILI9341 Display).
*   **Real-time Monitoring:**
    *   pH (Acid/Base)
    *   EC (Electrical Conductivity / PPM)
    *   Water Temperature (DS18B20)
    *   Water Level (Ultrasonic HC-SR04)
*   **Automated Dosing:** Controls 4 peristaltic pumps (pH Down, pH Up, Nutrient A, Nutrient B).
*   **Dual Interface:**
    *   **Local:** Color TFT Display.
    *   **Remote:** Web Dashboard via WiFi.
*   **Safety First:** Timeout logic to prevent over-dosing.

## 📂 Project Structure
*   `docs/`: Documentation (Guides, BOM, etc.) - [English](docs/en/index.md) | [Deutsch](docs/de/index.md)
*   `firmware/`: PlatformIO source code for the ESP32.
*   `hardware/`: Schematics, 3D print files, and wiring diagrams.

## 🚀 Quick Start
1.  **Hardware:** Assemble the system according to the [Wiring Diagram](hardware/schematics/system_overview.svg).
2.  **Firmware:**
    *   Install [Visual Studio Code](https://code.visualstudio.com/) and the [PlatformIO](https://platformio.org/) extension.
    *   Open the `firmware` folder.
    *   Edit `src/modules/WebServer.cpp` to set your WiFi credentials.
    *   Upload to your LILYGO T4 board.
3.  **Usage:** Power on, calibrate sensors via the web interface, and let it grow!

## ⚠️ Disclaimer
This system handles water and electricity. Build carefully. Use a GFCI (RCD) outlet. The authors are not responsible for leaks, dead plants, or shocks.

## 🤝 Contributing
Contributions are welcome! Please see the [Issues](https://github.com/yourusername/rdwc-autodoser-t4/issues) tab.