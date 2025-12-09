#include "RelayManager.h"

RelayManager::RelayManager(uint8_t address) {
    _address = address;
    _pcf = new PCF8574(_address);
    _state = 0xFF; // Active LOW relays usually mean HIGH is OFF
}

bool RelayManager::begin() {
    if (!_pcf->begin()) {
        Serial.println("Error: PCF8574 not found! Check I2C wiring.");
        return false;
    }
    
    // Set all pins to HIGH (Relays OFF for Active LOW modules)
    // Adjust logic if your relay module is Active HIGH
    _state = 0xFF;
    _pcf->write8(_state);
    
    Serial.printf("RelayManager initialized at 0x%02X\n", _address);
    return true;
}

void RelayManager::setRelay(uint8_t channel, bool on) {
    if (channel > 7) return;

    if (on) {
        // Active LOW: Clear bit to turn ON
        _state &= ~(1 << channel);
    } else {
        // Active LOW: Set bit to turn OFF
        _state |= (1 << channel);
    }

    _pcf->write8(_state);
}

void RelayManager::allOff() {
    _state = 0xFF; // All HIGH
    _pcf->write8(_state);
}

