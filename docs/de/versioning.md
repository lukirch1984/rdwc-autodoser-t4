# Versionierungs-Strategie

Dieses Projekt folgt [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Format: `MAJOR.MINOR.PATCH`

*   **MAJOR**: Inkompatible API- oder Hardware-Änderungen (z.B. Wechsel von I2C auf SPI Relais).
*   **MINOR**: Neue Funktionen, rückwärtskompatibel (z.B. neuer Sensortyp).
*   **PATCH**: Rückwärtskompatible Bugfixes (z.B. Korrektur einer Formel).

## Branching Modell
*   `main`: Stabiler Produktions-Code.
*   `develop`: Integrations-Branch für neue Features.
*   `feature/*`: Temporäre Branches für spezifische Features.
