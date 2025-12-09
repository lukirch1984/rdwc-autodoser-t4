#include "AppWebServer.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Sensors.h" // To get sensor data
#include "../data_types.h" // Include common data types

// Define the global WebServer instance here
WebServer server(80); 

void handleRoot() {
    SensorData data = Sensors::getData();
    String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<title>RDWC Auto-Doser</title>";
    html += "<style>body{font-family: Arial, sans-serif; margin: 20px;} h1{color:#333;} p{font-size:1.2em;}</style>";
    html += "<meta http-equiv=\"refresh\" content=\"5\">"; // Auto-refresh every 5 seconds
    html += "</head><body>";
    html += "<h1>RDWC Auto-Doser Status</h1>";
    html += "<p><b>pH:</b> " + String(data.ph, 2) + "</p>";
    html += "<p><b>EC:</b> " + String(data.ec, 2) + " mS/cm</p>";
    html += "<p><b>Temperature:</b> " + String(data.temp, 1) + " &deg;C</p>";
    html += "<p><b>Water Level:</b> " + String(data.waterLevel, 1) + " cm</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void AppWebServer::init() {
    WiFi.mode(WIFI_STA);
    // Hardcoded for now. In a real project, this would be handled via WiFiManager or AP mode setup.
    // For testing, replace with your actual SSID and PASSWORD
    const char* ssid = "YOUR_WIFI_SSID";
    const char* password = "YOUR_WIFI_PASSWORD";

    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        server.on("/", handleRoot);
        server.begin();
        Serial.println("Web Server initialized.");
    } else {
        Serial.println("\nFailed to connect to WiFi. Web server not started.");
    }
}

void AppWebServer::handleClient() {
    server.handleClient();
}

