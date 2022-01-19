#include "RoboBarman.h"

RoboBarman::RoboBarman() = default;

void RoboBarman::prepareBar()
{
    displayInterfaceHandler.setup();
    proximitySensorController.setup();
    while (proximitySensorController.objectIsPresent()) {
        //todo DISPLAY OUTPUT: DEJ TU SKLENICKU PRYC BRASKO
    }
    scaleController.setup();
    cartController.setup();
    cartController.calibrate();
    syrupDispensers.setup();
    waterDispensers.setup();
}

void RoboBarman::acceptDrinkOrder()
{
    while (!drinkConfer.configurationComplete()) {
        drinkConfer.setDrinkContent(displayInterfaceHandler.getDrinkData());
    };
}

void RoboBarman::makeDrink()
{
    for (int i = 0; i < 4; i++) {
        if (bitRead(*drinkConfer.drinkContentsPtr, i+1)) {
            cartController.moveToPos(i, forward);

            syrupDispensers.openValve(i);
            delay(200);

            float lastMessuredWeight = scaleController.getWeight();
            while (scaleController.getWeight() > lastMessuredWeight+2) {
                lastMessuredWeight = scaleController.getWeight();
            }

            syrupDispensers.closeValve(i);
        }
    }
    cartController.calibrate();
}

void RoboBarman::serveDrink()
{}

void RoboBarman::cleanupBar()
{
    displayInterfaceHandler.ardDisplaySerial.print("page pStart");
    displayInterfaceHandler.writeUselessBytes();

    *drinkConfer.drinkContentsPtr = B10000000;
}
