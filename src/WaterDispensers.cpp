#include "WaterDispensers.h"

WaterDispensers::WaterDispensers() : compressorPin{0}, pins{A2, A1, A0}
{}

void WaterDispensers::setup(){
    for (uint8_t pin:pins) {
        pinMode(pin, OUTPUT);
    }
}

void WaterDispensers::compressorState(bool state)
{
    digitalWrite(pins[compressorPin], state);
}

void WaterDispensers::routeState(uint8_t route, bool state)
{
    digitalWrite(pins[route], state);
}
