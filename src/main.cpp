#include "CartController.h"
#include "ProximitySensorController.h"
#include "ScaleController.h"
#include <Arduino.h>
#include "DisplayInterfaceHandler.h"
#include "DrinkPreparator.h"
#include <Servo.h>
#include "SyrupDispensers.h"

CartController cartController {};
ProximitySensorController proximitySensorController {};
ScaleController scaleController {};
DisplayInterfaceHandler displayInterfaceHandler {};
DrinkPreparator drinkPreparator {};
SyrupDispensers syrupDispensers{};

const uint8_t a = 0;
const uint8_t b = 1;
const uint8_t c = 2;
const uint8_t d = 3;

void setup()
{
    Serial.begin(9600);

    proximitySensorController.setupControlPins(5, 4);
    bool isObjectPresent = proximitySensorController.objectIsPresent();

    Serial.println("proximity");

    scaleController.init();
    Serial.println("scale");

    cartController.setupControlPins(19, 17, 18, 7);
    cartController.setStepDelay(70);
    cartController.calibrate();

    Serial.println("calibrated");

    cartController.allowMovement();

    cartController.moveToPos(cartController.positions[a], forward);
    syrupDispensers.openValve(a);
    delay(3000);
    syrupDispensers.closeValve(a);
    delay(100);
    cartController.moveToPos(cartController.positions[b], forward);
    delay(100);
    cartController.moveToPos(cartController.positions[c], forward);
    syrupDispensers.openValve(c);
    delay(3000);
    syrupDispensers.closeValve(c);
    delay(100);
    cartController.moveToPos(cartController.positions[d], forward);
    delay(100);

    cartController.calibrate();
    cartController.blockMovement();

    /*displayInterfaceHandler.setupControlPins();

    while (!drinkPreparator.readyToProceed()){
        drinkModifier.setDrinkContent(displayInterfaceHandler.getDrinkData());
    };*/
}

void loop()
{
}