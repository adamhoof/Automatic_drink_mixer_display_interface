#pragma once

#include "ProximitySensor.h"
#include <AceSorting.h>

class ProximitySensorController
{
private:
    ProximitySensor proximitySensor {};
public:
    void init();

    unsigned long sendPulses();

    double convertPulseToCm(unsigned long proximity);

    double getProximity();

    bool objectIsPresent();
};
