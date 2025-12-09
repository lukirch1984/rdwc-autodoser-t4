# Relay & Pump Assembly Guide

**Note:** This guide assumes you are using the I2C Architecture with the PCF8574.

## Connection
1. Connect the PCF8574 I/O Expander to the I2C Bus.
2. Connect the Relay Module inputs to P0-P3 of the PCF8574.
    *   **P0:** pH Down
    *   **P1:** pH Up
    *   **P2:** Nutrient A
    *   **P3:** Nutrient B

## Power
*   Power the Relays with 5V (from Buck Converter).
*   Power the Pumps with 12V (Direct from PSU, switched via Relay COM/NO).
