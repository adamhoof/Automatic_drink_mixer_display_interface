#pragma once

#include <Arduino.h>
#include "Cart.h"

#define forward true
#define backward false

const int32_t initPos{0};
const int32_t calibValidatePos{2000};
const int32_t aPos{16000};
const int32_t bPos{37500};
const int32_t cPos{59000};
const int32_t dPos{83000};

class CartController {
private:
    Cart cart;

public:
    CartController();
    void setPins();
    void setStepDelay(uint8_t stepDel);
    void calibrate();
    void setDir(bool dir);
    void step(uint8_t stpDelay);
    void moveToPos(const int32_t *targetPos, bool direction);
    bool isInitPos() const;
    void blockMovement() const;
    void allowMovement() const;
};