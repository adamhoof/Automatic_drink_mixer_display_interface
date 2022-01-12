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
const uint8_t right = 1;
const uint8_t left = 2;

void setup()
{
    scaleController.init();

    waterDispensers.setup();
    waterDispensers.routeState(right, on);
    waterDispensers.compressorState(on);
    delay(20000);
    waterDispensers.compressorState(off);
    waterDispensers.routeState(right, off);

    /*proximitySensorController.setupControlPins(5, 4);
    bool isObjectPresent = proximitySensorController.objectIsPresent();

    syrupDispensers.setup();

    syrupDispensers.openValve(a);
    delay(3000);
    syrupDispensers.closeValve(a);
    delay(100);*/

    /*Serial.begin(9600);

    scaleController.init();

    cartController.setControlPins(19, 17, 18, 7);
    cartController.setStepDelay(70);
    cartController.calibrate();

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