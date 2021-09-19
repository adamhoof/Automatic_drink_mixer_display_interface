#include "CartController.h"

CartController::CartController() = default;

void CartController::setPins() {
    pinMode(cart.motorEnablePin, OUTPUT);
    pinMode(cart.dirPin, OUTPUT);
    pinMode(cart.stepPin, OUTPUT);
    pinMode(cart.endSwitchPin, INPUT);
}

void CartController::setStepDelay(uint8_t stepDel) {
    cart.stepDelay = stepDel;
}

void CartController::setDir(bool dir) {
    digitalWrite(cart.dirPin, dir);
    if (dir == forward) { cart.dir = 1; }
    else if (dir == backward) { cart.dir = -1; }
    else { return; }
}

void CartController::calibrate() {
    setDir(backward);
    while (!isInitPos()) {
        step(cart.stepDelay);
    }
    cart.pos = 0;
    moveToPos(&initPos);
    }

void CartController::step(uint8_t stpDelay) {
    digitalWrite(cart.stepPin, HIGH);
    delayMicroseconds(stpDelay);
    digitalWrite(cart.stepPin, LOW);
    delayMicroseconds(stpDelay);
}

void CartController::moveToPos(const int32_t *targetPos) {
    setDir(forward);
    for (; cart.pos < *targetPos; cart.pos += cart.dir) {
        step(cart.stepDelay);
    }
}

bool CartController::isInitPos() const {
    return digitalRead(cart.endSwitchPin);
}

void CartController::blockMovement() const{
    digitalWrite(cart.motorEnablePin, LOW);
}

void CartController::allowMovement() const {
    digitalWrite(cart.motorEnablePin, HIGH);
}

