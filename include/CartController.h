#pragma once

#include <Arduino.h>
#include "Cart.h"

#define forward true
#define backward false

class CartController
{
private:
    Cart cart {};
    const uint8_t start = 4;
    const uint8_t calibValidate = 5;
    const uint16_t validatingPeriod = 3000;
public:
    CartController();

    void setupControlPins(uint8_t motorEnPin, uint8_t dirPin, uint8_t stepPin, uint8_t endSwitchPin);

    void setStepDelay(const uint8_t& stepDel);

    void calibrate();

    void setDir(const bool& dir);

    void move() const;

    void moveToPos(uint8_t posIndex, const bool& dir);

    void correctFalseInitPos() const;

    bool isInitPos() const;

    void blockMovement() const;

    void allowMovement() const;

    const int32_t positions[6];
};
