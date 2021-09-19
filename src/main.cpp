#include <Arduino.h>
#include "DrinkPreparator.h"
#include "SerialCommunicationHandler.h"
#include "CartController.h"

CartController cartController{};

void setup() {
    cartController.setPins();
    cartController.setStepDelay(80);
    cartController.allowMovement();
    cartController.calibrate();

    //glass checking logic
}

void loop() {

}
