#pragma once

#include <Arduino.h>

#define forward true
#define backward false

const int32_t initPos{0};
const int32_t aPos{16000};
const int32_t bPos{37500};
const int32_t cPos{59000};
const int32_t dPos{83000};

class CartController {
public:
    const uint8_t motorEnablePin{A5};
    const uint8_t dirPin{A3};
    const uint8_t stepPin{A4};
    const uint8_t endSwitchPin{7};
    int8_t currentDir{0};
    int32_t cartPos{1};

    CartController();
    void setup();
    void calibrate();
    void setDir(bool dir);
    void step(uint8_t speed);
    void moveToPos(int32_t targetPos);
};