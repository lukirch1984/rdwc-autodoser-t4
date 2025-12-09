# Usage Guide

## System Startup
1.  Ensure all sensors are submerged.
2.  Power on the 12V PSU.
3.  The Display will show a boot screen and perform a **Relay Self-Test** (clicking sound).
4.  Once "READY" appears, the main dashboard loads.

## Calibration (v1.0)
Currently, calibration values are defined in `SensorManager.cpp`.
To calibrate:
1.  Measure a known buffer (e.g., pH 7.0).
2.  Note the raw voltage (enable debug logging in code to see this).
3.  Update the `7.0` midpoint in the formula: `ph = 7.0 + ((MidpointVolt - Voltage) / Slope)`.
4.  Re-upload firmware.

*Runtime calibration via UI is planned for v1.1.*

## Web Interface
1.  Connect to the WiFi network defined in `AppWebServer.cpp`.
2.  Open the IP address shown in the Serial Monitor.
3.  View live stats remotely.
