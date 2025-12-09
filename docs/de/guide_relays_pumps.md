# Bauanleitung: Relais-Modul & Dosierpumpen anschließen

Diese Anleitung erklärt, wie du das 4-Kanal-Relais-Modul und die 12V-Peristaltikpumpen für die automatische Dosierung (pH Up/Down, Dünger A/B) anschließt.

## ⚠️ Sicherheitshinweis
Hier arbeiten wir mit **12V und höheren Strömen** (für die Pumpen). Ein Kurzschluss kann Kabel zum Schmelzen bringen oder das Netzteil beschädigen.
*   Arbeite immer spannungsfrei (Netzteil ausstecken).
*   Achte auf korrekte Polung (+/-).
*   Isoliere alle offenen Kontakte sorgfältig.

---

## 🛠 Benötigte Teile
1.  **4-Kanal Relais-Modul (5V)**
    *   Hinweis: Das Modul benötigt 5V Versorgungsspannung (vom Buck-Converter), lässt sich aber meist mit den 3.3V-Signalen des ESP32 schalten.
2.  **4x Peristaltik-Dosierpumpen (12V)**
3.  **12V Netzteil** (mind. 3A - 5A empfohlen)
4.  **Kabel** (Dickerer Querschnitt für die 12V-Leitungen, z.B. 0.5mm² oder 0.75mm²)
5.  **Verteilerklemmen** (z.B. Wago-Klemmen) für die 12V-Verteilung.

---

## ⚡ Schritt 1: Relais-Logik verkabeln (ESP32 -> Modul)

Das Relais-Modul fungiert als Schalter. Der ESP32 gibt nur das Signal ("Schalte an"), der Strom für die Spulen kommt von den 5V.

| Relais-Modul Pin | Anschlussziel | Anmerkung |
| :--- | :--- | :--- |
| **GND** | **GND** (System-Masse) | Gemeinsame Masse ist wichtig! |
| **VCC** | **5V** (Buck-Converter) | Spulenversorgung (nicht vom ESP32-3.3V Pin!) |
| **IN1** (pH Down) | **GPIO 16** | |
| **IN2** (pH Up) | **GPIO 17** | |
| **IN3** (Nut A) | **GPIO 19** | |
| **IN4** (Nut B) | **GPIO 21** | |

> **Info:** Die meisten Relais-Module sind "Active LOW". Das bedeutet, sie schalten ein, wenn am Pin *GND* (Low) anliegt. Unsere Firmware berücksichtigt das (`RELAY_ON = LOW`).

---

## 🔋 Schritt 2: Pumpen-Stromkreis (12V -> Relais -> Pumpe)

Wir nutzen das Relais, um die 12V-Leitung zur Pumpe zu unterbrechen.

**Das Prinzip pro Pumpe:**
1.  **12V (+) vom Netzteil** geht an den **Mittelkontakt (COM)** des Relais.
2.  Vom **Schließer-Kontakt (NO - Normally Open)** des Relais geht ein Kabel zum **Plus-Pol (+) der Pumpe**.
3.  Der **Minus-Pol (-) der Pumpe** geht direkt zurück an **GND (-) des Netzteils**.

**Schritt-für-Schritt Verkabelung:**

1.  **12V Verteilung:** Lege ein rotes Kabel vom 12V-Netzteil (+) zu einer Verteilerklemme. Von dort führe 4 Kabel zu den **COM (Common / Mitte)** Anschlüssen aller 4 Relais.
2.  **Masse Verteilung:** Lege ein schwarzes Kabel vom 12V-Netzteil (-) zu einer Verteilerklemme. Verbinde alle **Minus-Kabel der Pumpen** mit dieser Klemme.
3.  **Geschaltetes Plus:**
    *   Verbinde Relais 1 **NO** -> Plus-Kabel **Pumpe 1** (pH Down)
    *   Verbinde Relais 2 **NO** -> Plus-Kabel **Pumpe 2** (pH Up)
    *   Verbinde Relais 3 **NO** -> Plus-Kabel **Pumpe 3** (Dünger A)
    *   Verbinde Relais 4 **NO** -> Plus-Kabel **Pumpe 4** (Dünger B)

---

## 🧪 Schritt 3: Testlauf

1.  **Noch keine Flüssigkeiten!** Teste erst "trocken", um Überschwemmungen zu vermeiden.
2.  Schalte das System ein.
3.  Im Display oder Web-Interface sollten (wenn Sensorwerte Schwellenwerte unterschreiten) die Pumpen anspringen.
4.  Du solltest ein deutliches "Klicken" des Relais hören und die Pumpen sollten sich drehen.
5.  **Drehrichtung prüfen:** Peristaltikpumpen pumpen je nach Polung in eine Richtung. Prüfe, ob sie saugen/drücken wie gewünscht. Wenn falsch herum: Pole einfach die Kabel an der Pumpe (+/-) um.

---

## 💡 Tipps zur Installation

*   **Rückflussverhinderer:** Installiere Rückschlagventile in den Schläuchen, damit die Nährlösung nicht zurück in die Vorratsbehälter läuft oder Nährstoffkonzentrat nicht ungewollt ins Becken tropft (Siphon-Effekt!).
*   **Freilaufdioden (Optional aber empfohlen):** Beim Abschalten induktiver Lasten (Motoren) entstehen Spannungsspitzen. Eine Diode (z.B. 1N4007), die in Sperrrichtung parallel zu den Pumpenanschlüssen geschaltet wird, schützt die Relais-Kontakte und reduziert Störungen im System.

---

**Fertig!** Deine Dosieranlage ist nun elektrisch einsatzbereit.
