# RDWC Auto-Doser T4

**Professioneller Open Source Hydroponik-Controller für LILYGO TTGO T4 V1.3**

Der **RDWC Auto-Doser T4** ist ein hochpräziser Controller für Recirculating Deep Water Culture (RDWC) Systeme. Er nutzt das ESP32-basierte LILYGO T4 Display-Modul zur Überwachung von pH-Wert, EC-Wert, Temperatur und Wasserstand und dosiert automatisch Nährstoffe nach.

!!! warning "Hardware-Warnung: I2C-Erweiterung zwingend erforderlich"
    Das LILYGO T4 V1.3 belegt fast alle GPIO-Pins für das interne ILI9341-Display und den SD-Kartenslot.
    **Es ist NICHT möglich, Relais oder analoge Sensoren direkt anzuschließen.**
    
    Diese Firmware setzt zwingend auf den **I2C-Bus (SDA: 21, SCL: 22)** zur Erweiterung:
    
    *   **Relais:** Müssen über einen **PCF8574** I/O-Expander gesteuert werden.
    *   **pH / EC:** Müssen über einen **ADS1115** 16-Bit ADC eingelesen werden (der interne ESP32 ADC ist zu ungenau und Pins fehlen).

## Hauptfunktionen

*   **Präzise Überwachung:** 16-Bit ADC (ADS1115) für Labor-genaue pH- und EC-Messungen.
*   **Sicherheit:** Relais sind galvanisch über I2C entkoppelt.
*   **Visuelles Interface:** Saubere 320x240 UI mit Echtzeit-Updates.
*   **Modularer Code:** Strikte Trennung von Treibern, UI und Logik.

## Hardware-Setup

| Komponente | Anschluss | Anmerkung |
| :--- | :--- | :--- |
| **Relais-Modul** | I2C (0x20) | via PCF8574 |
| **pH-Sonde** | I2C (0x48) | via ADS1115 (A0) |
| **EC-Sonde** | I2C (0x48) | via ADS1115 (A1) |
| **Temp (DS18B20)** | GPIO 25 | OneWire |
| **Level (HC-SR04)** | Trig: 26, Echo: 39 | |

## Erste Schritte

Schaue dir die [Verkabelungsanleitung](../wiring.md) an (Englisch), um Details zum Aufbau zu erfahren.