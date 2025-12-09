# Bedienungsanleitung

## Systemstart
1.  Stelle sicher, dass alle Sensoren eingetaucht sind.
2.  Schalte das 12V Netzteil ein.
3.  Das Display zeigt einen Boot-Screen und führt einen **Relais-Selbsttest** durch (Klicken).
4.  Sobald "READY" erscheint, lädt das Dashboard.

## Kalibrierung (v1.0)
Aktuell sind Kalibrierwerte in `SensorManager.cpp` definiert.
Vorgehen:
1.  Miss eine bekannte Lösung (z.B. pH 7.0).
2.  Notiere die Rohspannung (aktiviere Debug-Log im Code).
3.  Aktualisiere den `7.0` Mittelpunkt in der Formel: `ph = 7.0 + ((MittelpunktVolt - Spannung) / Steigung)`.
4.  Firmware neu hochladen.

*Laufzeit-Kalibrierung über UI ist für v1.1 geplant.*

## Web Interface
1.  Verbinde dich mit dem WLAN (definiert in `AppWebServer.cpp`).
2.  Öffne die IP-Adresse aus dem Seriellen Monitor.
3.  Betrachte Live-Daten aus der Ferne.
