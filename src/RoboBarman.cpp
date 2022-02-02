#include "RoboBarman.h"

RoboBarman::RoboBarman() = default;

void RoboBarman::prepareBar()
{
    displayInterfaceHandler.setup();
    proximitySensorController.setup();
    bool sentPageUpdate = false;
    while (!proximitySensorController.objectIsPresent(16)) {
        if (sentPageUpdate) {
            continue;
        }
        displayInterfaceHandler.changePage(placeObjectPage);
        sentPageUpdate = true;
    }
    displayInterfaceHandler.changePage(initPage);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing scale controller...");
    delay(tillGlassIsPlaced);
    scaleController.setup();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
    delay(cosmeticDelay);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing cart controller...");
    cartController.setup();
    cartController.calibrate();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
    delay(cosmeticDelay);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing syrup dispensers...");
    syrupDispensers.setup();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
    delay(cosmeticDelay);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing water dispensers...");
    waterDispensers.setup();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "25");
    delay(cosmeticDelay);
}

void RoboBarman::acceptDrinkOrder()
{
    displayInterfaceHandler.changePage(createDrinkPage);

    while (!drinkConfer.configurationComplete()) {
        drinkConfer.setContent(displayInterfaceHandler.getContentUpdate());
    };
}

void RoboBarman::makeDrink()
{
    for (int i = 0; i < 4; i++) {
        if (bitRead(*drinkConfer.drinkContentsPtr, i + 1)) {
            cartController.moveToPos(i, forward);

            syrupDispensers.openValve(i);
            delay(tillWaterReachesGlass/2);

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
    delay(tillWaterReachesGlass);

    float lastMessuredWeight = scaleController.getWeight();

    while (scaleController.getWeight() > lastMessuredWeight + 2 && lastMessuredWeight <= 200) {
        lastMessuredWeight = scaleController.getWeight();
    }
    waterDispensers.compressorState(off);

    waterDispensers.routeState(requiredRoute, off);
}

void RoboBarman::serveDrink()
{
    while (proximitySensorController.objectIsPresent(16)) {
        bool sentPageUpdate = false;
        while (proximitySensorController.objectIsPresent(16)) {
            if (sentPageUpdate) {
                continue;
            }
            displayInterfaceHandler.changePage(placeObjectPage);
            sentPageUpdate = true;
        }
    }
}

void RoboBarman::cleanupBar()
{
    drinkConfer.resetContents();

    cartController.calibrate();

    displayInterfaceHandler.changePage(createDrinkPage);
}
