#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "SensorManager.h" // For SensorData

// --- Configuration ---
// Ideally load these from ConfigManager later, but hardcoded for MVP
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASS "YOUR_PASS"
#define MQTT_SERVER "192.168.1.100" // Example Broker IP
#define MQTT_PORT 1883
#define MQTT_TOPIC_STATUS "rdwc/status"

class NetworkManager {
private:
    WiFiClient _espClient;
    PubSubClient _mqttClient;
    
    unsigned long _lastMqttAttempt = 0;
    unsigned long _lastPublish = 0;

    void reconnectMqtt();

public:
    NetworkManager();
    void begin();
    void update(SensorData data); // Handles Connection & Publishing
};
