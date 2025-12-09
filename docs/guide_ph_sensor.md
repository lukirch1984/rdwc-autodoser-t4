# pH Sensor Assembly Guide

**Note:** This guide assumes you are using the I2C Architecture with the ADS1115.

## Connection
1. Connect the pH Probe to the BNC connector on the signal board.
2. Connect the Signal Board's Analog Output (PO) to **A0** on the ADS1115.
3. Power the Signal Board (usually 3.3V or 5V, check spec).

## Calibration
1. Dip probe in pH 7.0 buffer.
2. Read the raw voltage via the Display.
3. Update `SensorManager.cpp` with the measured midpoint voltage.
