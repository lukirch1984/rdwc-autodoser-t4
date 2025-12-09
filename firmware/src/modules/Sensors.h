#ifndef SENSORS_H
#define SENSORS_H

#include "data_types.h" // Include common data types

class Sensors {
public:
    static void init();
    static void update();
    static SensorData getData();
};

#endif
