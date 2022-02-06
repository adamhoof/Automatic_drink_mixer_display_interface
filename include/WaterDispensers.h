#pragma once

#include <Arduino.h>

#define OFF false
#define ON true

class WaterDispensers
{
private:
    const uint8_t compressorPin;
    const uint8_t pins[3];
public:

    WaterDispensers();

    void setup();

    void compressorState(bool state);

    void routeState(uint8_t routeIndex, bool state);
};
