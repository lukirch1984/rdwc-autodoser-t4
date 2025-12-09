#include <Arduino.h>
#include <WebServer.h> // Ensure WebServer library is processed globally first
#include "data_types.h" // Include common data types
#include "config.h"
#include "modules/DisplayUI.h"
#include "modules/Sensors.h"
#include "modules/Dosing.h"
#include "modules/AppWebServer.h" // Include AppWebServer module header

// Task Handles
TaskHandle_t TaskSensorsHandle;
TaskHandle_t TaskWiFiHandle;
TaskHandle_t TaskUIHandle;

// Task Functions
void TaskSensorsCode(void * pvParameters);
void TaskWiFiCode(void * pvParameters);
void TaskUICode(void * pvParameters);

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println("Starting RDWC Auto-Doser T4...");

  // Init Hardware
  pinMode(PIN_BUZZER, OUTPUT);
  
  // Create Tasks
  // Core 1: Sensors & Control Logic (Real-time critical)
  xTaskCreatePinnedToCore(
    TaskSensorsCode,   "SensorsTask",   TASK_SENSOR_STACK_SIZE,   NULL,  1,  &TaskSensorsHandle,   1
  );

  // Core 1: UI (Can share core with sensors, or move to 0 if heavy)
  xTaskCreatePinnedToCore(
    TaskUICode,        "UITask",        TASK_UI_STACK_SIZE,       NULL,  1,  &TaskUIHandle,        1
  );

  // Core 0: WiFi & WebServer (Network stack runs on Core 0)
  xTaskCreatePinnedToCore(
    TaskWiFiCode,      "WiFiTask",      TASK_WIFI_STACK_SIZE,     NULL,  1,  &TaskWiFiHandle,      0
  );
}

void loop() {
  // Main loop is empty as we use FreeRTOS tasks
  vTaskDelete(NULL);
}

// --- Task Implementations ---

void TaskSensorsCode(void * pvParameters) {
  Sensors::init();
  Dosing::init();
  
  for(;;) {
    Sensors::update(); // Read pH, EC, Temp, Level
    vTaskDelay(pdMS_TO_TICKS(1000)); // 1s Loop
  }
}

void TaskUICode(void * pvParameters) {
  DisplayUI::init();
  
  for(;;) {
    DisplayUI::update(); // Refresh screen
    vTaskDelay(pdMS_TO_TICKS(100)); // 10fps refresh
  }
}

// Moved TaskWiFiCode definition after WebServer.h include
void TaskWiFiCode(void * pvParameters) {
  AppWebServer::init();
  
  for(;;) {
    AppWebServer::handleClient();
    vTaskDelay(pdMS_TO_TICKS(10)); // Allow other low prio tasks
  }
}

