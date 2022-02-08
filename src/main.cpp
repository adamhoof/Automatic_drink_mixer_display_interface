#include "RoboBarman.h"

RoboBarman roboBarman{};

void setup()
{
    roboBarman.prepareBar();
    Serial.begin(9600);
}

void loop()
{
    roboBarman.acceptDrinkOrder();
    roboBarman.makeDrink();
    roboBarman.serveDrink();
    roboBarman.closeBar();
}
