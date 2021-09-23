#pragma once

#include "Scale.h"

class ScaleController{
public:
    ScaleController();

    HX711_ADC scale{doutPin, sckPin};

    void init();

    float getWeight();
};