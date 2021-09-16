#include <Arduino.h>
#include "DrinkPreparator.h"
#include "SerialCommunicationHandler.h"
#include "CartController.h"

CartController cartController{};

void setup()
{
    cartController.setup();
    cartController.calibrate();
}

void loop()
{
    cartController.moveToPos(aPos);
    delay(500);
    cartController.moveToPos(bPos);
    delay(500);
    cartController.moveToPos(cPos);
    delay(500);
    cartController.moveToPos(dPos);
    delay(500);

    cartController.moveToPos(initPos);
}
