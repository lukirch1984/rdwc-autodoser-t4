# Bauanleitung: pH-Sensor Modul an LILYGO T4 anschließen

Diese Anleitung beschreibt detailliert, wie du ein analoges pH-Sensor-Modul (z.B. Typ DFRobot Gravity oder ähnlich) an das LILYGO T4 Board anschließt.

## ⚠️ Wichtige Warnung vorab
Der ESP32 arbeitet mit **3.3V Logikspannung**. Viele pH-Module geben jedoch bis zu **5V** aus. Der direkte Anschluss kann den ESP32 zerstören! Prüfe unbedingt die Ausgangsspannung deines Sensors oder verwende die unten beschriebene 3.3V-Versorgungsmethode.

---

## 🛠 Benötigte Teile & Werkzeuge
1.  **LILYGO T4 V1.3** (ESP32 Board)
2.  **pH-Sensor Kit** (Sonde + BNC-Interface Platine)
3.  **Jumper-Kabel** (Female-Female oder Female-Male, je nach Header)
4.  **Lötkolben & Lötzinn** (für stabile Verbindungen am Board)
5.  **Multimeter** (zum Prüfen der Spannung)

---

## ⚡ Schritt 1: Pin-Identifikation

### Am pH-Interface-Board (Sensor-Seite)
Das kleine Board, an dem die BNC-Sonde angeschlossen wird, hat meist 3 Pins:
*   **VCC** (oder + / V): Spannungsversorgung
*   **GND** (oder - / G): Masse
*   **PO** (oder A / Signal): Analoger pH-Ausgang

### Am LILYGO T4 Board (Controller-Seite)
Wir nutzen folgende Pins (siehe `config.h`):
*   **3.3V**: Zur Versorgung des Sensors (sicherste Methode)
*   **GND**: Gemeinsame Masse
*   **GPIO 34**: Analoger Eingang (ADC1_CH6)

> **Hinweis zu GPIO 34:** Dies ist ein "Input Only" Pin, der sich hervorragend für analoge Messungen eignet. Er hat keinen internen Pull-Up/Down Widerstand, was für Sensoren ideal ist.

---

## 🔌 Schritt 2: Verkabelung

Wir versorgen den Sensor direkt mit 3.3V vom ESP32. Die meisten "5V"-Sensoren funktionieren auch mit 3.3V, liefern dann aber einen entsprechend skalierten Ausgangswert (0-3.3V statt 0-5V), was perfekt für den ESP32-Eingang ist.

| pH-Modul Pin | LILYGO T4 Pin | Kabelfarbe (Vorschlag) |
| :--- | :--- | :--- |
| **VCC** | **3.3V** | Rot |
| **GND** | **GND** | Schwarz |
| **PO / Signal** | **GPIO 34** | Blau / Gelb |

**Anleitung:**
1.  Verbinde **GND** des pH-Moduls mit einem **GND**-Pin am T4.
2.  Verbinde **VCC** des pH-Moduls mit dem **3.3V**-Pin am T4.
3.  Verbinde den **Signalausgang (PO)** mit **GPIO 34**.

---

## 🧪 Schritt 3: Test & Kalibrierung

Da wir den Sensor mit 3.3V statt 5V betreiben, stimmen die Standard-Werte der Hersteller nicht mehr zu 100%. Das System muss kalibriert werden.

1.  **System einschalten:** Verbinde das T4 per USB. Das Display sollte starten.
2.  **Sonde anschließen:** Stecke die pH-Sonde per BNC-Stecker an das Interface-Board.
3.  **In Pufferlösung 7.0 tauchen:**
    *   Halte die Sonde in pH 7.0 Kalibrierflüssigkeit.
    *   Warte 1-2 Minuten, bis sich der Wert stabilisiert.
    *   Lies den *analogen Rohwert* aus (dieser wird aktuell noch nicht im UI angezeigt, kann aber über `Serial.print` im Code ausgegeben werden - *Feature für v1.1: Rohwert-Anzeige im Menü*).
    *   Passe in `config.h` den Wert `PH_ANALOG_MID_POINT` an diesen gemessenen Wert an.
4.  **In Pufferlösung 4.0 tauchen:**
    *   Reinige die Sonde mit destilliertem Wasser.
    *   Halte sie in pH 4.0 Lösung.
    *   Der Analogwert sollte sich ändern. Passe ggf. `PH_ANALOG_SLOPE` an, falls die Spreizung nicht stimmt.

---

## 💡 Troubleshooting

*   **Wert springt wild hin und her?**
    *   Überprüfe die GND-Verbindung. Eine schlechte Masse ist die Hauptursache für Rauschen.
    *   Verwende ein separates Netzteil für den ESP32, nicht den USB-Port des Laptops, falls möglich.
*   **Wert ist immer 0 oder 4095?**
    *   Prüfe die Verkabelung. Signal an falschem Pin?
    *   Sonde defekt? (Glaskolben gebrochen?)

---

**Nächster Schritt:** Wiederhole diesen Vorgang für den EC-Sensor an **GPIO 35**.
