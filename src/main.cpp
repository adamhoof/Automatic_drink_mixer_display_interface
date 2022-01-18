#include "CartController.h"
#include "ProximitySensorController.h"
#include "ScaleController.h"
#include <Arduino.h>
#include "DisplayInterfaceHandler.h"
#include "DrinkConfigurator.h"
#include "SyrupDispensers.h"
#include "WaterDispensers.h"
#include "RoboBarman.h"

RoboBarman roboBarman{};

CartController cartController {};
ProximitySensorController proximitySensorController {};
ScaleController scaleController {};
DisplayInterfaceHandler displayInterfaceHandler {};
DrinkConfigurator drinkConfer {};
SyrupDispensers syrupDispensers{};
WaterDispensers waterDispensers{};

void setup()
{
    roboBarman.prepareBar();

    cartController.calibrate();

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

    /*proximitySensorController.setup(5, 4);
    bool isObjectPresent = proximitySensorController.objectIsPresent();

    scaleController.setup();

    cartController.moveToPos(a, forward);
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
    delay(100);

    cartController.calibrate();*/

    /*displayInterfaceHandler.setup();*/

    while (!drinkConfer.readyToProceed()){
        drinkConfer.setDrinkContent(displayInterfaceHandler.getDrinkData());
    };
}

void loop()
{
    roboBarman.acceptDrinkOrder();
    roboBarman.makeDrink();
    roboBarman.serveDrink();
    roboBarman.cleanupBar();
}
