#pragma once

#include <Arduino.h>
#include "Cart.h"

#define forward true
#define backward false

class CartController {
private:
    Cart cart{};
public:
    CartController();
    void setPins();
    void setStepDelay(const uint8_t& stepDel);
    void calibrate();
    void setDir(const bool& dir);
    void move() const;
    void moveToPos(const int32_t& targetPos, const bool& dir);
    void correctFalseInitPos() const;
    bool isInitPos() const;
    void blockMovement() const;
    void allowMovement() const;
    enum positions{
        start = 0,
        calibValidate = 1300,
        a = 16000,
        b = 37500,
        c = 59000,
        d = 83000
    }positions;
    const uint16_t validatingPeriod = 3000;
};
