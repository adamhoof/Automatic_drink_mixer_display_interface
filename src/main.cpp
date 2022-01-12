#include "CartController.h"
#include "ProximitySensorController.h"
#include "ScaleController.h"
#include <Arduino.h>
#include "DisplayInterfaceHandler.h"
#include "DrinkPreparator.h"
#include "SyrupDispensers.h"
#include "WaterDispensers.h"

CartController cartController {};
ProximitySensorController proximitySensorController {};
ScaleController scaleController {};
DisplayInterfaceHandler displayInterfaceHandler {};
DrinkPreparator drinkPreparator {};
SyrupDispensers syrupDispensers{};
WaterDispensers waterDispensers{};

const uint8_t a = 0;
const uint8_t b = 1;
const uint8_t c = 2;
const uint8_t d = 3;

void setup()
{
    cartController.setControlPins(19, 17, 18, 7);
    syrupDispensers.setup();
    waterDispensers.setup();

    cartController.setStepDelay(70);
    cartController.calibrate();

    cartController.moveToPos(a, forward);

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
    waterDispensers.routeState(RIGHT, off);

    /*proximitySensorController.setupControlPins(5, 4);
    bool isObjectPresent = proximitySensorController.objectIsPresent();

    scaleController.init();

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

    /*displayInterfaceHandler.setControlPins();

    while (!drinkPreparator.readyToProceed()){
        drinkPreparator.modifyContents(displayInterfaceHandler.getDrinkData());
    };*/
}

void loop()
{
}
