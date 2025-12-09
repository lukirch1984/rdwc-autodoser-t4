#pragma once

#include <Arduino.h>
#include "PCF8574.h"

class RelayManager {
private:
    PCF8574* _pcf;
    uint8_t _address;
    uint8_t _state; // Cache for current state

public:
    RelayManager(uint8_t address = 0x20); // Default PCF8574 address
    bool begin();
    
    // Control individual relays (0-7)
    void setRelay(uint8_t channel, bool on);
    
    // Safety
    void allOff();
};
