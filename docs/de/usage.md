# Bedienungsanleitung

## Systemstart
1.  Stelle sicher, dass alle Sensoren eingetaucht sind.
2.  Schalte das 12V Netzteil ein.
3.  Das Display zeigt einen Boot-Screen und führt einen **Relais-Selbsttest** durch (Klicken).
4.  Sobald "READY" erscheint, lädt das Dashboard.

## Kalibrierung (Persistent)
Kalibrierwerte für pH und EC sowie die Dosierziele werden nun **dauerhaft** im Flash-Speicher (NVS) des ESP32 mit Hilfe des `ConfigManager` gespeichert. Die Werte bleiben also nach einem Neustart erhalten.

*   **Aktuelle Methode:** Zurzeit müssen Kalibrierwerte (z.B. `phMidpointVolt`, `ecKFactor`) direkt in `src/drivers/ConfigManager.cpp` angepasst und die Firmware neu hochgeladen werden, um neue Standardwerte zu setzen.
*   **Zukunft:** Ein Kalibrierungsmenü zur Laufzeit über die Benutzeroberfläche oder das Web-Interface ist geplant.

## Sicherheitsfunktionen (Fail-Safe Dosierung)
Der `DosingManager` implementiert mehrere Fail-Safe-Mechanismen:
*   **Plausibilitätsprüfung:** Die Dosierung wird gestoppt, wenn Sensorwerte (pH, EC) außerhalb realistischer Grenzen liegen.
*   **Pumpen-Timeout:** Eine einzelne Pumpe läuft maximal `DOSING_TIMEOUT_MS` (10 Sekunden) am Stück.
*   **Abklingzeit:** Nach jeder Dosierung wartet das System `DOSING_COOLDOWN_MS` (15 Minuten), damit sich die Lösung vermischen kann, bevor eine weitere Dosis erfolgt.

## Datenprotokollierung (SD-Karte)
Sensordaten (pH, EC, Temperatur, Wasserstand) werden alle `LOG_INTERVAL_MS` (5 Minuten) in die Datei `datalog.csv` auf der SD-Karte geschrieben.
*   **Dateiformat:** CSV (`Zeit,pH,EC,Temp,Level`)
*   **Zugriff:** Entnehme die SD-Karte und lese sie an einem Computer aus.

## MQTT-Konnektivität
Der `NetworkManager` verwaltet die WiFi- und MQTT-Verbindungen.
*   **Konfiguration:** Richte deine WiFi-SSID, Passwort und MQTT-Broker-Details in `src/drivers/NetworkManager.h` ein.
*   **Datenformat:** Sensordaten werden alle 10 Sekunden als JSON-String an das MQTT-Topic `rdwc/status` gesendet.
*   **Beispiel-Topic:** `rdwc/status`
*   **Beispiel-Payload:** `{"ph":6.12, "ec":1.35, "temp":22.8, "level":15.3}`

## Web-Interface (Zukunft)
Das frühere Web-Interface wurde zugunsten von MQTT deaktiviert. Ein robusteres und konfigurierbareres Web-Interface ist für zukünftige Versionen geplant.