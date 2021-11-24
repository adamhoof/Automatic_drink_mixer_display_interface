#pragma once

#include <Arduino.h>

class ProximitySensor
{
public:
    ProximitySensor();

    uint8_t trigPin {};
    uint8_t echoPin {};
};
