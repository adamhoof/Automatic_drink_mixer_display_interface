#pragma once

#include "ProximitySensor.h"

class ProximitySensorController{
public:
    ProximitySensor proximitySensor{};

    void init();

    unsigned long sendPulses();

    double convertPulseToCm(unsigned long proximity);

    double getProximity();
};