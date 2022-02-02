#pragma once

#include <Arduino.h>
#include "DisplayInterfaceHandler.h"

#define idPos 0
#define valPos 1
#define idA 1
#define idB 2
#define idC 3
#define idD 4
#define idWater 5
#define idCancelButton 6
#define idMakeDrinkButton 7

class DrinkConfigurator
{
public:
    uint8_t drinkContents {};
    uint8_t* drinkContentsPtr {};
public:
    DrinkConfigurator();

    void setContent(const uint8_t* receivedIdAndValue) const;

    bool configurationComplete() const;

    void resetContents() const;
};
