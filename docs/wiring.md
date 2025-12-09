# Wiring Guide (Hardware Setup)

This guide details how to connect the LILYGO T4 to the external I2C modules.

## System Overview Diagram
![System Overview](assets/system_overview.svg)

## Wiring Architecture (Mermaid)

```mermaid
graph TD
    ESP32[LILYGO T4 ESP32]
    
    subgraph I2C_Bus [I2C Bus (SDA:21, SCL:22)]
        ADS[ADS1115 ADC]
        PCF[PCF8574 Expander]
    end
    
    ESP32 -->|I2C| ADS
    ESP32 -->|I2C| PCF
    
    subgraph Sensors
        PH[pH Probe] -->|Analog| ADS
        EC[EC Probe] -->|Analog| ADS
        DS18[DS18B20 Temp] -->|GPIO 25| ESP32
        US[HC-SR04 Level] -->|GPIO 26/39| ESP32
    end
    
    subgraph Actuators
        PCF -->|Digital| R1[Relay 1: pH Down]
        PCF -->|Digital| R2[Relay 2: pH Up]
        PCF -->|Digital| R3[Relay 3: Nut A]
        PCF -->|Digital| R4[Relay 4: Nut B]
    end
```

## I2C Bus Connection
The LILYGO T4 uses **SDA: GPIO 21** and **SCL: GPIO 22**. You must connect these to your sensors and relays.

| LILYGO T4 | Component |
| :--- | :--- |
| 3.3V | VCC (Check component voltage!) |
| GND | GND |
| GPIO 21 (SDA) | SDA |
| GPIO 22 (SCL) | SCL |

## ADS1115 (Sensors)
*   **Address:** 0x48 (Addr pin to GND)
*   **A0:** pH Sensor Signal
*   **A1:** EC Sensor Signal

## PCF8574 (Relays)
*   **Address:** 0x20 (All switches OFF/GND)
*   **P0:** Pump 1 (pH Down)
*   **P1:** Pump 2 (pH Up)
*   **P2:** Pump 3 (Nutrient A)
*   **P3:** Pump 4 (Nutrient B)