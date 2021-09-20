#include <Arduino.h>
#include "DrinkPreparator.h"
#include "SerialCommunicationHandler.h"
#include "CartController.h"
#include "HX711_ADC.h"
#include <EEPROM.h>

HX711_ADC LoadCell{3, 2}; //dout 3, sck 2

/*CartController cartController{};*/


const int calVal_eepromAdress = 0;
unsigned long millisNow = 0;

void setup() {
    Serial.begin(57600);
    delay(10);
    Serial.println();
    Serial.println("Starting...");

    LoadCell.begin();
    float calibrationValue; // calibration value (see example file "Calibration.ino")
    calibrationValue = 731.43; // uncomment this if you want to set the calibration value in the sketch

    unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
    boolean _tare = true; //set this to false if you don'millisNow want tare to be performed in the next step
    LoadCell.start(stabilizingtime, _tare);
    if (LoadCell.getTareTimeoutFlag()) {
        Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
        while (1);
    } else {
        LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
        Serial.println("Startup is complete");
    }
}

void loop() {

    LoadCell.update();
    float i = LoadCell.getData();

    Serial.print("Load_cell output val: ");
    Serial.println(i);
}


