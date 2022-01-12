#pragma once

#include <Arduino.h>

#define off false
#define on true

class WaterDispensers
{
private:
    const uint8_t compressorPin;
    uint8_t pins[3];
public:

    WaterDispensers();

    void setup();

    void compressorState(bool state);

    void routeState(uint8_t route, bool state);
};
