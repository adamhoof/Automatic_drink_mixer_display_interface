#include "RoboBarman.h"

RoboBarman roboBarman{};

void setup()
{
    Serial.begin(9600);
    roboBarman.prepareBar();

    /*cartController.moveToPos(a, forward);

    syrupDispensers.openValve(a);
    delay(2700);
    syrupDispensers.closeValve(a);

    cartController.moveToPos(c, forward);

    syrupDispensers.openValve(c);
    delay(2700);
    syrupDispensers.closeValve(c);

    cartController.moveToPos(calibValidate, backward);

    waterDispensers.routeState(RIGHT, on);
    waterDispensers.compressorState(on);
    delay(10000);
    waterDispensers.compressorState(off);
    waterDispensers.routeState(RIGHT, off);*/

    /*cartController.moveToPos(a, forward);
    syrupDispensers.openValve(a);
    delay(3000);
    syrupDispensers.closeValve(a);
    delay(100);
    cartController.moveToPos(b, forward);
    delay(100);
    cartController.moveToPos(c, forward);
    syrupDispensers.openValve(c);
    delay(3000);
    syrupDispensers.closeValve(c);
    delay(100);
    cartController.moveToPos(d, forward);
    delay(100);*/
}

void loop()
{
    roboBarman.acceptDrinkOrder();
    /*roboBarman.makeDrink();
    roboBarman.serveDrink();
    roboBarman.cleanupBar();*/
}
