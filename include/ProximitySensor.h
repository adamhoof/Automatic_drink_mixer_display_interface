#pragma once

#include <Arduino.h>

class ProximitySensor
{
public:
    ProximitySensor();

    const uint8_t trigPin {};
    const uint8_t echoPin {};
};
