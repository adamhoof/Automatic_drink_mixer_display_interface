#include "CartController.h"
#include <Arduino.h>

CartController cartController{};

void setup() {
    Serial.begin(9600);
    cartController.setPins();
    cartController.setStepDelay(70);
    cartController.calibrate();
    cartController.blockMovement();
}

void loop() {
}
