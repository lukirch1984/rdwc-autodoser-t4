# Versioning Strategy

This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Format: `MAJOR.MINOR.PATCH`

*   **MAJOR**: Incompatible API or Hardware changes (e.g., changing from I2C to SPI relays).
*   **MINOR**: Add functionality in a backwards compatible manner (e.g., adding a new sensor type).
*   **PATCH**: Backwards compatible bug fixes (e.g., fixing a calibration formula).

## Branching Model
*   `main`: Stable production code.
*   `develop`: Integration branch for new features.
*   `feature/*`: Temporary branches for specific features.
