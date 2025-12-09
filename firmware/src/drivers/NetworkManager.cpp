#include "NetworkManager.h"

NetworkManager::NetworkManager() : _mqttClient(_espClient) {
}

void NetworkManager::begin() {
    // 1. WiFi Init
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("[Network] Connecting to WiFi");
    
    // Non-blocking WiFi check in update(), but initial attempt here
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[Network] WiFi Connected!");
        Serial.print("IP: "); Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n[Network] WiFi connection skipped (will retry).");
    }

    // 2. MQTT Init
    _mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void NetworkManager::reconnectMqtt() {
    if (!_mqttClient.connected()) {
        if (millis() - _lastMqttAttempt > 5000) {
            _lastMqttAttempt = millis();
            Serial.print("[Network] Attempting MQTT connection...");
            
            // Client ID
            String clientId = "RDWC-T4-";
            clientId += String(random(0xffff), HEX);

            if (_mqttClient.connect(clientId.c_str())) {
                Serial.println("connected");
            } else {
                Serial.print("failed, rc=");
                Serial.print(_mqttClient.state());
                Serial.println(" try again in 5 seconds");
            }
        }
    }
}

void NetworkManager::update(SensorData data) {
    // 1. Ensure WiFi
    if (WiFi.status() != WL_CONNECTED) {
        // Simple reconnect logic could go here
        return;
    }

    // 2. Ensure MQTT
    if (!_mqttClient.connected()) {
        reconnectMqtt();
    }
    _mqttClient.loop();

    // 3. Publish Data (Every 10 seconds)
    if (millis() - _lastPublish > 10000) {
        _lastPublish = millis();
        
        // Manual JSON construction
        char msg[128];
        snprintf(msg, 128, "{\"ph\":%.2f, \"ec\":%.2f, \"temp\":%.1f, \"level\":%.1f}", 
                 data.ph, data.ec, data.temp, data.waterLevel);
        
        if (_mqttClient.publish(MQTT_TOPIC_STATUS, msg)) {
            Serial.println("[Network] MQTT Published");
        }
    }
}
