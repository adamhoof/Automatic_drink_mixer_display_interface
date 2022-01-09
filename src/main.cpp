#include "CartController.h"
#include "ProximitySensorController.h"
#include "ScaleController.h"
#include <Arduino.h>
#include "DisplayInterfaceHandler.h"
#include "DrinkPreparator.h"

CartController cartController {};
ProximitySensorController proximitySensorController {};
ScaleController scaleController {};
DisplayInterfaceHandler displayInterfaceHandler {};
DrinkPreparator drinkPreparator {};

const uint8_t a = 0;
const uint8_t b = 1;
const uint8_t c = 2;
const uint8_t d = 3;

void setup()
{
    Serial.begin(9600);

    proximitySensorController.setupControlPins(5, 4);
    bool isObjectPresent = proximitySensorController.objectIsPresent();

    scaleController.init();

    cartController.setupControlPins(19, 17, 18, 7);
    cartController.setStepDelay(70);
    cartController.calibrate();

    cartController.moveToPos(a, forward);
    delay(100);
    cartController.moveToPos(b, forward);
    delay(100);
    cartController.moveToPos(c, forward);
    delay(100);
    cartController.moveToPos(d, forward);
    delay(100);

    cartController.calibrate();

    /*displayInterfaceHandler.setupControlPins();

    while (!drinkPreparator.readyToProceed()){
        drinkPreparator.modifyContents(displayInterfaceHandler.getDrinkData());
    };*/
}

void loop()
{
}