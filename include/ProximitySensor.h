#pragma once

#include <Arduino.h>

class ProximitySensor{
public:
    ProximitySensor();

    const uint8_t trigPin{5};
    const uint8_t echoPin{4};
};