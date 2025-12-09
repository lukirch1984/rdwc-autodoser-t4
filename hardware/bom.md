# Bill of Materials (BOM) - RDWC Auto-Doser T4

This is a comprehensive list of components required to build the RDWC Auto-Doser T4 system. Links are provided as examples and may vary based on availability and region.

## 1. Main Controller
*   **LILYGO T4 V1.3 ESP32 Development Board with ILI9341 LCD Display**
    *   *Description:* The core of the system, integrates ESP32 with a color TFT display.
    *   *Approx. Price:* €25-€35
    *   *Example Link:* [Search for "LILYGO T4 V1.3 ESP32 ILI9341"](https://www.google.com/search?q=LILYGO+T4+V1.3+ESP32+ILI9341)

## 2. Sensors
*   **pH Sensor Kit** (e.g., DFRobot Analog pH Sensor Pro or similar)
    *   *Description:* Measures the acidity/alkalinity of the nutrient solution.
    *   *Approx. Price:* €20-€40
    *   *Example Link:* [DFRobot Gravity: Analog pH Sensor / Meter Kit V2](https://www.dfrobot.com/product-1823.html)
*   **EC / TDS Sensor Kit** (e.g., DFRobot Analog EC Sensor or similar)
    *   *Description:* Measures the electrical conductivity (nutrient concentration) of the solution.
    *   *Approx. Price:* €20-€40
    *   *Example Link:* [DFRobot Gravity: Analog Electrical Conductivity Sensor / Meter Kit V2](https://www.dfrobot.com/product-1824.html)
*   **DS18B20 Waterproof Temperature Sensor**
    *   *Description:* Measures water temperature for accurate pH/EC readings and system health.
    *   *Approx. Price:* €5-€10
    *   *Example Link:* [DS18B20 Waterproof Temperature Sensor](https://www.google.com/search?q=DS18B20+waterproof)
*   **HC-SR04 Ultrasonic Distance Sensor**
    *   *Description:* Measures the water level in the reservoir.
    *   *Approx. Price:* €2-€5
    *   *Example Link:* [HC-SR04 Ultrasonic Sensor](https://www.google.com/search?q=HC-SR04+ultrasonic+sensor)

## 3. Actuators
*   **4-Channel 5V Relay Module**
    *   *Description:* Controls the 12V peristaltic pumps from the 3.3V/5V logic of the ESP32.
    *   *Approx. Price:* €5-€10
    *   *Example Link:* [4 Channel 5V Relay Module](https://www.google.com/search?q=4+channel+5v+relay+module)
*   **4x Peristaltic Dosing Pumps** (12V, e.g., 3mmx5mm hose, 100ml/min)
    *   *Description:* For precise dosing of pH Up, pH Down, Nutrient A, and Nutrient B.
    *   *Approx. Price:* €10-€20 per pump (€40-€80 total)
    *   *Example Link:* [12V Peristaltic Pump](https://www.google.com/search?q=12V+peristaltic+dosing+pump)

## 4. Power Supply & Conversion
*   **12V DC Power Supply** (e.g., 5A, sufficient for pumps and ESP32)
    *   *Description:* Main power source for the entire system.
    *   *Approx. Price:* €15-€25
    *   *Example Link:* [12V 5A Power Supply](https://www.google.com/search?q=12V+5A+power+supply)
*   **DC-DC Buck Converter** (e.g., LM2596 based, 12V to 5V)
    *   *Description:* Steps down 12V to 5V to power the LILYGO T4 board (via USB or 5V pin).
    *   *Approx. Price:* €2-€5
    *   *Example Link:* [LM2596 Buck Converter](https://www.google.com/search?q=LM2596+buck+converter)

## 5. Other Essential Components
*   **Wires & Jumper Wires:**
    *   *Description:* Assorted male-female, male-male, female-female jumper wires for prototyping.
    *   *Approx. Price:* €5-€10
*   **Waterproof Enclosure / Project Box:**
    *   *Description:* To house the electronics safely away from water and humidity.
    *   *Approx. Price:* €10-€30
*   **Silicon Tubing / Hoses:** (e.g., 3mm ID x 5mm OD)
    *   *Description:* For the peristaltic pumps. Ensure food-grade if relevant.
    *   *Approx. Price:* €5-€15 (per meter)
*   **Calibration Fluids:**
    *   *Description:* For accurate sensor calibration (pH 4.0, 7.0, 10.0; EC standard solution).
    *   *Approx. Price:* €10-€20 per set
*   **RDWC Buckets / Reservoirs:**
    *   *Description:* Your main hydroponic system components (e.g., 5-gallon buckets, larger reservoir).
    *   *Note:* Not included in the system's BOM, but essential for the project.

## Estimated Total Cost (excl. RDWC buckets):
Approximately **€180 - €300**, depending on supplier, quality, and region.

---
*Disclaimer: Prices are estimates and subject to change. Always check current pricing from reputable suppliers.*
