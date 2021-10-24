#include "CartController.h"
#include "ProximitySensorController.h"
#include "ScaleController.h"
#include <Arduino.h>

CartController cartController{};
ProximitySensorController proximitySensorController{};
ScaleController scaleController{};

void setup() {
    Serial.begin(9600);
    cartController.init();
    proximitySensorController.init();
    bool isGlass = proximitySensorController.objectIsPresent();
    Serial.println(isGlass);

    /*scaleController.init();
    cartController.setStepDelay(70);
    cartController.calibrate();
    cartController.blockMovement();*/
}

void loop() {

}