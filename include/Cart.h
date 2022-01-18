#pragma once

#include <Arduino.h>

class Cart
{
public:
    Cart();

    const uint8_t motorEnablePin {};
    const uint8_t dirPin {};
    const uint8_t stepPin {};
    const uint8_t endSwitchPin {};
    uint8_t stepDelay {};
    int8_t dir {};
    int32_t pos {};
};
