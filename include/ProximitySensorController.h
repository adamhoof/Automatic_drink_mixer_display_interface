#pragma once

#include "ProximitySensor.h"
#include <AceSorting.h>

class ProximitySensorController
{
private:
    ProximitySensor proximitySensor {};
public:
    void setup();

    unsigned long sendPulse();

    double convertPulseToCm(unsigned long proximity);

    double getProximity();

    bool objectIsPresent(uint8_t numOfSamples);
};
