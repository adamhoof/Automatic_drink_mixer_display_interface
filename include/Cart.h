#pragma once

#include <Arduino.h>

class Cart
{
public:
    Cart();

    uint8_t motorEnablePin {};
    uint8_t dirPin {};
    uint8_t stepPin {};
    uint8_t endSwitchPin {};
    uint8_t stepDelay {80};
    int8_t dir {-1};
    int32_t pos {0};
};
