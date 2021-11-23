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

void setup()
{
    Serial.begin(9600);

    proximitySensorController.init();
    bool isObjectPresent = proximitySensorController.objectIsPresent();
    Serial.println(isObjectPresent);

    scaleController.init();
    scaleController.getWeight();

    cartController.init();
    cartController.setStepDelay(70);
    cartController.calibrate();
    cartController.blockMovement();

    /*displayInterfaceHandler.init();

    while (!drinkPreparator.readyToProceed()){
        drinkPreparator.modifyContents(displayInterfaceHandler.getDrinkData());
    };*/
}

void loop()
{

}