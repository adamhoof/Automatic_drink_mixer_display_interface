#include "RoboBarman.h"

RoboBarman::RoboBarman() = default;

void RoboBarman::prepareBar()
{
    displayInterfaceHandler.setup();
    proximitySensorController.setup();
    displayInterfaceHandler.changePage(placeObjectPage);

    while (!proximitySensorController.objectIsPresent(16)) {}

    displayInterfaceHandler.changePage(initPage);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing scale controller...");
    delay(tillGlassIsPlaced);
    scaleController.setup();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "33");
    delay(cosmeticDelay);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing cart controller...");
    cartController.setup();
    cartController.calibrate();
    displayInterfaceHandler.updateProgressBar(initProgressBar, "33");
    delay(cosmeticDelay);
    displayInterfaceHandler.updateTextField(initTextField, "Initializing syrup dispensers...");
    syrupDispensers.setup();
    delay(cosmeticDelay);
    displayInterfaceHandler.updateProgressBar(initProgressBar, "33");
    waterDispensers.setup();
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
        if (bitRead(*drinkConfer.getAllContents(), i + 1)) {
            cartController.moveToPos(i, FORWARD);

            syrupDispensers.open(i);
            delay(tillWaterReachesGlass/1.5);

            float lastMessuredWeight = scaleController.getWeight();
            while (scaleController.getWeight() > lastMessuredWeight + 2) {
                lastMessuredWeight = scaleController.getWeight();
            }

            syrupDispensers.close(i);
            delay(200);
            syrupDispensers.refill(i);

        }
    }
    cartController.moveToPos(lilAwayFromSwitch, BACKWARD);

    uint8_t requiredRoute;

    bitRead(*drinkConfer.getAllContents(), idWater) ? requiredRoute = RIGHT
                                                    : requiredRoute = LEFT;

    waterDispensers.routeState(requiredRoute, ON);

    waterDispensers.compressorState(ON);
    delay(tillWaterReachesGlass);

    float lastMessuredWeight = scaleController.getWeight();

    while (scaleController.getWeight() > lastMessuredWeight + 2 && lastMessuredWeight <= 250) {
        lastMessuredWeight = scaleController.getWeight();
    }
    waterDispensers.compressorState(OFF);

    waterDispensers.routeState(requiredRoute, OFF);
}

void RoboBarman::serveDrink()
{
    displayInterfaceHandler.ardDisplaySerial.print(takeDrinkPage); //I don't know why the hell do I have to use this instead
    displayInterfaceHandler.writeUselessBytes(); //of my function changePage that literary does the same and works till this moment in code

    while (proximitySensorController.objectIsPresent(16)) {}
}

void RoboBarman::closeBar()
{
    void(* resetFunc) (void) = nullptr;
    resetFunc();
}
