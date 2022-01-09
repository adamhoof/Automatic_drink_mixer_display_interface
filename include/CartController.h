#pragma once

#include <Arduino.h>
#include "Cart.h"

#define forward true
#define backward false
const int32_t start = 0;
const int32_t calibValidate = 1300;

class CartController
{
private:
    Cart cart {};

    const uint16_t validatingPeriod{3000};
    const uint8_t startIndex{4};
    const uint8_t calibValidateIndex{5};
public:
    CartController();

    int32_t positions[6];

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
};
