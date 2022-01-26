#include "RoboBarman.h"

RoboBarman roboBarman{};

void setup()
{
    Serial.begin(9600);
    roboBarman.prepareBar();
}

void loop()
{
    roboBarman.acceptDrinkOrder();
    roboBarman.makeDrink();
    roboBarman.cleanupBar();
}
