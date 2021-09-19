#pragma once

#include <Arduino.h>
#include "Cart.h"

#define forward true
#define backward false

const int32_t initPos{1000};
const int32_t aPos{16000};
const int32_t bPos{37500};
const int32_t cPos{59000};
const int32_t dPos{83000};

class CartController {
private:
    Cart cart;
    /*const uint8_t motorEnablePin{A5};
    const uint8_t dirPin{A3};
    const uint8_t stepPin{A4};
    const uint8_t endSwitchPin{7};
    uint8_t stepDelay{80};
    int8_t dir{0};
    int32_t cartPos{0};*/
public:
    CartController();
    void setPins();
    void setStepDelay(uint8_t stepDel);
    void calibrate();
    void setDir(bool dir);
    void step(uint8_t stpDelay);
    void moveToPos(const int32_t *targetPos);
    bool isInitPos() const;
    void blockMovement() const;
    void allowMovement() const;
};