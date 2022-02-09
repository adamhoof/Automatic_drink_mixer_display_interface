#include "RoboBarman.h"

RoboBarman roboBarman {};

void setup()
{
    roboBarman.prepareBar();
}

void loop()
{
    roboBarman.acceptDrinkOrder();
    roboBarman.makeDrink();
    roboBarman.serveDrink();
    roboBarman.closeBar();
}
