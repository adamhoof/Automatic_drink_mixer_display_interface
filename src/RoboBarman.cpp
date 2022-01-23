#include "RoboBarman.h"

RoboBarman::RoboBarman() = default;

void RoboBarman::prepareBar()
{
    displayInterfaceHandler.setup();
    proximitySensorController.setup();
    bool alreadySentPageUpdate = false;
    while (proximitySensorController.objectIsPresent()) {
        if (alreadySentPageUpdate) {
            continue;
        }
        displayInterfaceHandler.ardDisplaySerial.print("page pRemoveObject");
        displayInterfaceHandler.writeUselessBytes();
        alreadySentPageUpdate = true;
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
        if (bitRead(*drinkConfer.drinkContentsPtr, i + 1)) {
            cartController.moveToPos(i, forward);

            syrupDispensers.openValve(i);
            delay(200);

            float lastMessuredWeight = scaleController.getWeight();
            while (scaleController.getWeight() > lastMessuredWeight + 2) {
                lastMessuredWeight = scaleController.getWeight();
            }

            syrupDispensers.closeValve(i);
        }
    }
    cartController.moveToPos(calibValidate, backward);

    uint8_t requiredRoute {};

    bitRead(*drinkConfer.drinkContentsPtr, idWater) ? requiredRoute = RIGHT
                                                    : requiredRoute = LEFT;

    waterDispensers.routeState(requiredRoute, on);

    waterDispensers.compressorState(on);
    delay(10000);
    waterDispensers.compressorState(off);

    waterDispensers.routeState(requiredRoute, off);

    while (proximitySensorController.objectIsPresent()) {
        //todo DISPLAY OUTPUT: odeberte napoj
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
