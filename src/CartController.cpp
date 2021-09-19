#include "CartController.h"

CartController::CartController() = default;

void CartController::setPins() {
    pinMode(motorEnablePin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(endSwitchPin, INPUT);
}

void CartController::setStepDelay(uint8_t stepDel) {
    stepDelay = stepDel;
}

void CartController::setDir(bool dir) {
    digitalWrite(dirPin, dir);
    if (dir == forward) { currentDir = 1; }
    else if (dir == backward) { currentDir = -1; }
    else { return; }
}

void CartController::calibrate() {
    setDir(backward);
    while (!isInitPos()) {
        step(stepDelay);
    }
    cartPos = 0;
    moveToPos(&initPos);
    }

void CartController::step(uint8_t stpDelay) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stpDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stpDelay);
}

void CartController::moveToPos(const int32_t *targetPos) {
    setDir(forward);
    for (; cartPos < *targetPos; cartPos += currentDir) {
        step(stepDelay);
    }
}

bool CartController::isInitPos() const {
    return digitalRead(endSwitchPin);
}

void CartController::blockMovement() const{
    digitalWrite(motorEnablePin, LOW);
}

void CartController::allowMovement() const {
    digitalWrite(motorEnablePin, HIGH);
}

