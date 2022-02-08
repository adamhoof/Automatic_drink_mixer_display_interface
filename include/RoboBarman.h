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
public:
    const uint8_t cosmeticDelay {100};
    const uint16_t tillGlassIsPlaced{1500};
    const uint16_t tillWaterReachesGlass{3500};
    const uint16_t tillSyrupReachesGlass{2000};
    const uint8_t offset{2};
    const uint8_t finalDrinkWeight{250};
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

    void closeBar();

private:
    bool syrupSupplyIsEmpty(int initWeight, int lastMessuredWeight);
    bool pouringSyrup(int lastMessuredWeight);
    bool waterAmountNotSufficient(int lastMessuredWeight);
    bool waterSupplyIsEmpty(int initWeight, int lastMessuredWeight);
};

