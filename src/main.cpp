#include "RoboBarman.h"

RoboBarman roboBarman{};

void setup()
{
    roboBarman.prepareBar();
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
}

void loop()
{
    roboBarman.acceptDrinkOrder();
    roboBarman.makeDrink();
    roboBarman.serveDrink();
    roboBarman.closeBar();
}
