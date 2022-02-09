#include "RoboBarman.h"

RoboBarman::RoboBarman() = default;

bool RoboBarman::syrupSupplyIsEmpty(int initWeight, int lastMessuredWeight)
{
    return initWeight + offset > lastMessuredWeight;
}

bool RoboBarman::pouringSyrup(int lastMessuredWeight)
{
    return scaleController.getWeight() > lastMessuredWeight + offset;
}

bool RoboBarman::waterAmountNotSufficient(int lastMessuredWeight)
{
    return scaleController.getWeight() > lastMessuredWeight && lastMessuredWeight <= finalDrinkWeight;
}

bool RoboBarman::waterSupplyIsEmpty(int initWeight, int lastMessuredWeight)
{
    return initWeight + offset > lastMessuredWeight || lastMessuredWeight < finalDrinkWeight - offset;
}

void RoboBarman::closeBar()
{
    void (* resetFunc)(void) = nullptr;
    resetFunc();
}

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
    uint8_t divisionFactor = drinkConfer.calculateNumberOfContents();
    uint8_t errorsToBeDisplayed[5] {};

    for (int i = 0; i < 4; i++) {
        if (bitRead(*drinkConfer.getAllContents(), i + 1)) {
            cartController.moveToPos(i, FORWARD);

            syrupDispensers.open(i);
            delay(tillSyrupReachesGlass);

            int initWeight = scaleController.getWeight();
            int lastMessuredWeight = initWeight;

            while (pouringSyrup(lastMessuredWeight)) {
                lastMessuredWeight = scaleController.getWeight();
            };

            if (syrupSupplyIsEmpty(initWeight, lastMessuredWeight)) {
                errorsToBeDisplayed[i] = 1;
            }
            syrupDispensers.close(i);
            delay(200);
            syrupDispensers.refill(i);
            syrupDispensers.detach(i);
            delay(100);

            displayInterfaceHandler.ardDisplaySerial.print(prepProgressUpdates[divisionFactor]);
            displayInterfaceHandler.writeUselessBytes();
        }
    }

    cartController.moveToPos(lilAwayFromSwitch, BACKWARD);

    uint8_t requiredRoute;

    bitRead(*drinkConfer.getAllContents(), idWater) ? requiredRoute = RIGHT
                                                    : requiredRoute = LEFT;

    waterDispensers.routeState(requiredRoute, ON);

    int initWeight = scaleController.getWeight();
    int lastMessuredWeight = initWeight;

    waterDispensers.compressorState(ON);
    delay(tillWaterReachesGlass);

    while (waterAmountNotSufficient(lastMessuredWeight)) {
        lastMessuredWeight = scaleController.getWeight();
    }

    waterDispensers.compressorState(OFF);

    waterDispensers.routeState(requiredRoute, OFF);

    displayInterfaceHandler.ardDisplaySerial.print(prepProgressUpdates[divisionFactor]);
    displayInterfaceHandler.writeUselessBytes();

    if (waterSupplyIsEmpty(initWeight, lastMessuredWeight)) {
        errorsToBeDisplayed[4] = 1;
    }

    uint8_t numOfErrors {0};

    for (uint8_t errorIndex = 0; errorIndex < 5; errorIndex++) {
        if (errorsToBeDisplayed[errorIndex] == 1) {
            displayInterfaceHandler.ardDisplaySerial.print(errors[errorIndex]);
            displayInterfaceHandler.writeUselessBytes();
            delay(10);
            numOfErrors++;
        }
    }

    if (numOfErrors != 0) {
        while (proximitySensorController.objectIsPresent(32)) {}
        closeBar();
    }
}

void RoboBarman::serveDrink()
{
    displayInterfaceHandler.ardDisplaySerial.print(
            takeDrinkPage); //I don't know why the hell do I have to use this instead
    displayInterfaceHandler.writeUselessBytes(); //of my function changePage that literary does the same and works till this moment in code

    while (proximitySensorController.objectIsPresent(32)) {}
}
