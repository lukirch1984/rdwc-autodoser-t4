#include "DisplayUI.h"
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Sensors.h" // To get sensor data
#include "../data_types.h" // Include common data types

TFT_eSPI tft = TFT_eSPI();

void DisplayUI::init() {
    tft.init();
    tft.setRotation(1); // Landscape
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("RDWC Auto-Doser");
    Serial.println("Display UI initialized.");
}

void DisplayUI::update() {
    SensorData data = Sensors::getData();

    tft.fillRect(0, 40, tft.width(), tft.height() - 40, TFT_BLACK); // Clear data area

    tft.setCursor(10, 50);
    tft.print("pH: ");
    tft.println(data.ph, 2);

    tft.setCursor(10, 80);
    tft.print("EC: ");
    tft.println(data.ec, 2);

    tft.setCursor(10, 110);
    tft.print("Temp: ");
    tft.print(data.temp, 1);
    tft.println(" C");

    tft.setCursor(10, 140);
    tft.print("Level: ");
    tft.print(data.waterLevel, 1);
    tft.println(" cm");
}

