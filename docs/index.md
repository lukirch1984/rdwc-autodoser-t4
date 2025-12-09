# RDWC Auto-Doser T4

**Professional Open Source Hydroponic Controller for LILYGO TTGO T4 V1.3**

The **RDWC Auto-Doser T4** is a high-precision controller designed for Recirculating Deep Water Culture (RDWC) systems. It utilizes the ESP32-based LILYGO T4 display module to monitor pH, EC, temperature, and water levels, automatically dosing nutrients to maintain optimal conditions.

!!! warning "Hardware Requirement: I2C Expansion Essential"
    The LILYGO T4 V1.3 utilizes almost all GPIO pins for its internal ILI9341 display and SD card slot. 
    **You CANNOT connect relays or analog sensors directly to the remaining pins.**
    
    This firmware is strictly designed to use the **I2C Bus (SDA: 21, SCL: 22)** for expansion:
    
    *   **Relays:** Must use a **PCF8574** I/O Expander.
    *   **pH / EC:** Must use an **ADS1115** 16-bit ADC (internal ESP32 ADC is too noisy and pins are scarce).

## Key Features

*   **Precision Sensing:** Uses **ADS1115** (16-bit ADC) for lab-grade pH and EC with **Automatic Temperature Compensation (ATC)**.
*   **Safety & Reliability:** Implements **Fail-Safe** mechanisms (plausibility checks, dose timeouts, cooldowns) to protect your plants.
*   **Usability:** Calibration values and dosing targets are **persistently stored** in Flash memory (NVS).
*   **Data Logging:** Logs sensor data to **SD Card** every 5 minutes for long-term analysis.
*   **IoT Ready:** Sends live sensor data via **MQTT** to a broker (e.g., Home Assistant).
*   **Visual Interface:** Clean 320x240 UI with real-time updates and flicker-free rendering.
*   **Modular Code:** Separation of concerns (Drivers vs. UI vs. Logic).

## Hardware Setup

| Component | Connection | Notes |
| :--- | :--- | :--- |
| **Relay Module** | I2C (0x20) | via PCF8574 |
| **pH Probe** | I2C (0x48) | via ADS1115 (A0) |
| **EC Probe** | I2C (0x48) | via ADS1115 (A1) |
| **Temp (DS18B20)** | GPIO 25 | OneWire |
| **Level (HC-SR04)** | Trig: 26, Echo: 39 | |

## Getting Started

Check out the [Wiring Guide](wiring.md) for detailed schematics.