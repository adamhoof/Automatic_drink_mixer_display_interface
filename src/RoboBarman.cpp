#include "RoboBarman.h"

RoboBarman::RoboBarman() = default;

void RoboBarman::prepareBar()
{
    displayInterfaceHandler.setup();
    proximitySensorController.setup();
    while (!proximitySensorController.objectIsPresent()){
        //todo DISPLAY OUTPUT: DEJ TU SKLENICKU PRYC BRASKO
    }
    scaleController.setup();
    cartController.setup();
    syrupDispensers.setup();
    waterDispensers.setup();
}

void RoboBarman::acceptDrinkOrder()
{}

void RoboBarman::makeDrink()
{}

void RoboBarman::serveDrink()
{}

void RoboBarman::cleanupBar()
{}
