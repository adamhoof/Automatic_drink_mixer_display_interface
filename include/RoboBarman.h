#pragma once

#include "CartController.h"
#include "ProximitySensorController.h"
#include "ScaleController.h"
#include <Arduino.h>
#include "DisplayInterfaceHandler.h"
#include "DrinkConfigurator.h"
#include "SyrupDispensers.h"
#include "WaterDispensers.h"

const uint8_t a = 0;
const uint8_t b = 1;
const uint8_t c = 2;
const uint8_t d = 3;

class RoboBarman
{
private:
    CartController cartController {};
    ProximitySensorController proximitySensorController {};
    ScaleController scaleController {};
    DisplayInterfaceHandler displayInterfaceHandler {};
    DrinkConfigurator drinkConfer {};
    SyrupDispensers syrupDispensers{};
    WaterDispensers waterDispensers{};
public:
    RoboBarman();

    void prepareBar();

    void acceptDrinkOrder();

    void makeDrink();

    void serveDrink();

    void cleanupBar();
};

