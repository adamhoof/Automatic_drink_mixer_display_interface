#include "RoboBarman.h"

RoboBarman::RoboBarman() = default;

void RoboBarman::prepareBar()
{
    displayInterfaceHandler.setup();
    proximitySensorController.setup();
    bool sentPageUpdate = false;
    while (!proximitySensorController.objectIsPresent()) {
        if (sentPageUpdate) {
            continue;
        }
        displayInterfaceHandler.changePage(placeObjectPage);
        sentPageUpdate = true;
    }
    displayInterfaceHandler.changePage(initPage);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing scale controller...");
    scaleController.setup();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
    displayInterfaceHandler.updateTextField(initTextField, "Initializing cart controller...");
    cartController.setup();
    cartController.calibrate();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
    displayInterfaceHandler.updateTextField(initTextField, "Initializing syrup dispensers...");
    syrupDispensers.setup();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
    displayInterfaceHandler.updateTextField(initTextField, "Initializing syrup dispensers...");
    waterDispensers.setup();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
}

void RoboBarman::acceptDrinkOrder()
{
    displayInterfaceHandler.changePage(createDrinkPage);

    while (!drinkConfer.configurationComplete()) {
        drinkConfer.setDrinkContent(displayInterfaceHandler.getDrinkData());
    };
}

void RoboBarman::makeDrink()
{
    for (int i = 0; i < 4; i++) {
        if (bitRead(*drinkConfer.drinkContentsPtr, i + 1)) {
            *drinkConfer.requiredNumOfSyrupsPtr += 1;
            cartController.moveToPos(i, forward);

            syrupDispensers.openValve(i);
            delay(1000);

            float lastMessuredWeight = scaleController.getWeight();
            while (scaleController.getWeight() > lastMessuredWeight + 2) {
                lastMessuredWeight = scaleController.getWeight();
            }

            syrupDispensers.closeValve(i);

        }
        Serial.println("After valving");
        Serial.println(scaleController.getWeight());

        Serial.println(200-*drinkConfer.requiredNumOfSyrupsPtr*30);
    }
    cartController.moveToPos(calibValidate, backward);

    //TODO tare the scale here?

    uint8_t requiredRoute {};

    bitRead(*drinkConfer.drinkContentsPtr, idWater) ? requiredRoute = RIGHT
                                                    : requiredRoute = LEFT;

    waterDispensers.routeState(requiredRoute, on);

    waterDispensers.compressorState(on);
    delay(2500);

    float lastMessuredWeight = scaleController.getWeight();
    while (scaleController.getWeight() > lastMessuredWeight + 2 && lastMessuredWeight <= 200-*drinkConfer.requiredNumOfSyrupsPtr*30) {
        lastMessuredWeight = scaleController.getWeight();
    }
    waterDispensers.compressorState(off);

    waterDispensers.routeState(requiredRoute, off);

    Serial.println("After comping");
    Serial.println(scaleController.getWeight());

    while (proximitySensorController.objectIsPresent()) {
        //todo DISPLAY OUTPUT: odeberte napoj
    }
    cartController.calibrate();
}

void RoboBarman::serveDrink()
{}

void RoboBarman::cleanupBar()
{
    displayInterfaceHandler.changePage(createDrinkPage);

    drinkConfer.resetContents();
}
