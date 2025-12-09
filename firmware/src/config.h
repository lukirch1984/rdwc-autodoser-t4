#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==========================================
// SYSTEM SETTINGS
// ==========================================
#define SERIAL_BAUD 115200
#define SYSTEM_LANGUAGE_EN  // Change to SYSTEM_LANGUAGE_DE for German

// ==========================================
// PIN DEFINITIONS (LILYGO T4 V1.3)
// ==========================================

// --- Display (ILI9341 via TFT_eSPI) ---
// Configured in platformio.ini (build_flags)
// TFT_MOSI 23
// TFT_SCLK 18
// TFT_CS   27
// TFT_DC   32
// TFT_RST  5
// TFT_BL   4

// --- SD Card (Native SPI) ---
#define SD_MISO_PIN 2
#define SD_MOSI_PIN 15
#define SD_SCLK_PIN 14
#define SD_CS_PIN   13

// --- Sensors (Input) ---
#define PIN_PH_SENSOR   34  // ADC1_CH6
#define PIN_EC_SENSOR   35  // ADC1_CH7
#define PIN_TEMP_SENSOR 25  // DS18B20 OneWire
#define PIN_US_ECHO     33  // HC-SR04 Echo

// --- Actuators (Output) ---
#define PIN_US_TRIGGER  26  // HC-SR04 Trigger
#define PIN_RELAY_PH_DOWN 16
#define PIN_RELAY_PH_UP   17
#define PIN_RELAY_NUT_A   19
#define PIN_RELAY_NUT_B   21
#define PIN_BUZZER        22

// --- Inputs ---
#define PIN_BUTTON_1    36 // Reserve Input
#define PIN_BUTTON_2    39 // Reserve Input

// ==========================================
// TASKS CONFIGURATION
// ==========================================
#define TASK_SENSOR_STACK_SIZE 4096
#define TASK_WIFI_STACK_SIZE   8192
#define TASK_UI_STACK_SIZE     4096

// ==========================================
// TARGET VALUES (Dosing)
// ==========================================
#define TARGET_PH_MIN 5.8
#define TARGET_PH_MAX 6.2
#define TARGET_EC_MIN 1.4
#define TARGET_EC_MAX 1.6 // Max EC to avoid over-dosing, mainly for alerts

// ==========================================
// ADC & SENSOR CALIBRATION (Generic Placeholders)
// ==========================================
#define ADC_MAX_VALUE   4095.0  // 12-bit ADC
#define ADC_VREF        3.3     // ESP32 ADC reference voltage in Volts

// pH Sensor (Simplified Linear Model)
// Assumes pH 7.0 (neutral) at 2.5V (analog value around 3100 if input via voltage divider to 3.3V)
// For a typical pH probe, 0V might be pH 0, 5V might be pH 14, or 2.5V is pH 7.
// We'll assume a range of 0-5V mapped to 0-14 pH for simplicity in calculation, then adjust for 3.3V ADC.
// Let's assume pH 7.0 -> 1.5V (actual output of pH electrode after signal conditioning)
// And pH 4.0 -> 2.0V ; pH 10.0 -> 1.0V (example)
// A common analog value for pH 7.0 for some modules is around 1500mV.
// For ESP32 3.3V ADC: 1500mV / 3300mV * 4095 = 1861.
#define PH_ANALOG_MID_POINT 1861.0 // Analog reading for pH 7.0 (approx. 1.5V)
#define PH_ANALOG_SLOPE     -50.0  // Analog value change per pH unit (e.g., pH changes by 1 for 50 analog units)

// EC Sensor (Simplified Linear Model with Temperature Compensation)
// Assumes 0 EC at 0V and a certain EC at max voltage.
// 2.0 mS/cm might be at 3.0V.
// Analog value for 3.0V: 3000mV / 3300mV * 4095 = 3722.7
#define EC_ANALOG_HIGH_POINT 3722.0 // Analog reading for a known high EC (e.g., 2.0 mS/cm)
#define EC_KNOWN_HIGH_VALUE  2.0    // The EC value (mS/cm) corresponding to EC_ANALOG_HIGH_POINT
#define EC_TEMP_COMP_FACTOR  0.02   // Standard temperature compensation factor for EC

#endif
