#pragma once

#include <Arduino.h>
#include "Cart.h"

#define forward true
#define backward false
const int32_t start = 0;
const int32_t calibValidate = 1300;
const int32_t a = 16000;
const int32_t b = 37500;
const int32_t c = 59000;
const int32_t d = 83000;

class CartController
{
private:
    Cart cart {};
public:
    CartController();

    void setupControlPins(uint8_t motorEnPin, uint8_t dirPin, uint8_t stepPin, uint8_t endSwitchPin);

    void setStepDelay(const uint8_t& stepDel);

    void calibrate();

    void setDir(const bool& dir);

    void move() const;

    void moveToPos(const int32_t& targetPos, const bool& dir);

    void correctFalseInitPos() const;

    bool isInitPos() const;

    void blockMovement() const;

    void allowMovement() const;

    const uint16_t validatingPeriod = 3000;
};
