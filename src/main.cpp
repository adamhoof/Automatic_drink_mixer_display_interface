#include <Arduino.h>
#include "DrinkPreparator.h"
#include "SerialCommunicationHandler.h"
#include "CartController.h"
#include "HX711_ADC.h"
#include "ScaleController.h"

ScaleController scaleController{};

void setup() {
    scaleController.init();
    Serial.begin(57600);
}

void loop() {

    Serial.println(scaleController.getWeight());
}


