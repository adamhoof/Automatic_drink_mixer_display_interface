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
    displayInterfaceHandler.init();

    while (!drinkPreparator.readyToProceed()){
        drinkPreparator.modifyContents(displayInterfaceHandler.getDrinkData());
    };

    /*cartController.init();
    proximitySensorController.init();
    bool isGlass = proximitySensorController.objectIsPresent();
    Serial.println(isGlass);
*/
    /*scaleController.init();
    cartController.setStepDelay(70);
    cartController.calibrate();
    cartController.blockMovement();*/

}

void loop()
{

}