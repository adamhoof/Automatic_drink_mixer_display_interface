#pragma once

#include "ProximitySensor.h"

class ProximitySensorController{
private:
    ProximitySensor proximitySensor{};
public:
    void init();
    unsigned long sendPulses();
    double convertPulseToCm(unsigned long proximity);
    double getProximity();
};
