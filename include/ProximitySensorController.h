#pragma once

#include "ProximitySensor.h"
#include <AceSorting.h>

class ProximitySensorController
{
private:
    ProximitySensor proximitySensor {};
public:
    void setupControlPins(uint8_t trigPin, uint8_t echoPin);

    unsigned long sendPulses();

    double convertPulseToCm(unsigned long proximity);

    double getProximity();

    bool objectIsPresent();
};
