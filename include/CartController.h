#pragma once

#include <Arduino.h>

#define forward true
#define backward false
#define initPos 0
#define aPos 1
#define bPos 2
#define cPos 3
#define dPos 4


class CartController {
public:
    const uint8_t motorEnablePin{A5};
    const uint8_t dirPin{A3};
    const uint8_t stepPin{A4};
    const uint8_t endSwitchPin{7};
    const int32_t stationPositions [5]{0, 16000, 37500, 59000, 83000};
    int8_t currentDir{0};
    int32_t cartPos{0};

    CartController();
    void setup();
    void setDir(bool dir);
    void step();
    void moveToPos(int8_t pos);
};