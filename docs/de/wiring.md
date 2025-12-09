# Verkabelungsanleitung (Hardware Setup)

Diese Anleitung erklärt den Anschluss des LILYGO T4 an die externen I2C-Module.

## System-Übersicht
![System Overview](../assets/system_overview.svg)

## Architektur (Mermaid)

```mermaid
graph TD
    ESP32[LILYGO T4 ESP32]
    
    subgraph I2C_Bus [I2C Bus]
        ADS[ADS1115 ADC]
        PCF[PCF8574 Expander]
    end
    
    ESP32 -->|I2C| ADS
    ESP32 -->|I2C| PCF
    
    subgraph Sensoren
        PH[pH Sonde] -->|Analog| ADS
        EC[EC Sonde] -->|Analog| ADS
        DS18[DS18B20 Temp] -->|GPIO 25| ESP32
        US[HC-SR04 Level] -->|GPIO 26/39| ESP32
    end
    
    subgraph Aktoren
        PCF -->|Digital| R1[Relais 1: pH Down]
        PCF -->|Digital| R2[Relais 2: pH Up]
        PCF -->|Digital| R3[Relais 3: Dünger A]
        PCF -->|Digital| R4[Relais 4: Dünger B]
    end
```

## I2C-Bus Verbindung
Das LILYGO T4 nutzt **SDA: GPIO 21** und **SCL: GPIO 22**. Diese müssen mit Sensoren und Relais verbunden werden.

| LILYGO T4 | Komponente |
| :--- | :--- |
| 3.3V | VCC (Spannung prüfen!) |
| GND | GND |
| GPIO 21 (SDA) | SDA |
| GPIO 22 (SCL) | SCL |

## ADS1115 (Sensoren)
*   **Adresse:** 0x48 (Addr Pin auf GND)
*   **A0:** pH-Sensor Signal
*   **A1:** EC-Sensor Signal

## PCF8574 (Relays)
*   **Adresse:** 0x20 (Alle Schalter AUS/GND)
*   **P0:** Pumpe 1 (pH Down)
*   **P1:** Pumpe 2 (pH Up)
*   **P2:** Pumpe 3 (Dünger A)
*   **P3:** Pumpe 4 (Dünger B)