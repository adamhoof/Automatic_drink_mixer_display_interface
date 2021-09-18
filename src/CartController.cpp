#include "CartController.h"

CartController::CartController() = default;

void CartController::setup() {
    pinMode(motorEnablePin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(endSwitchPin, INPUT);
    digitalWrite(motorEnablePin, HIGH);
}

void CartController::setDir(bool dir) {
    digitalWrite(dirPin, dir);
    if (dir == forward) { currentDir = 1; }
    else if (dir == backward) { currentDir = -1; }
    else { return; }
}

void CartController::calibrate() {
    setDir(backward);
    while (!digitalRead(endSwitchPin)) {
        step(60);
    }
    setDir(forward);
    for (; cartPos < 1000; cartPos += currentDir) {
        step(60);
    }
}

void CartController::step(uint8_t stepDelay) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
}

void CartController::moveToPos(const int32_t *targetPos) {
    if (*targetPos != initPos) {
        setDir(forward);
        for (; cartPos < *targetPos; cartPos += currentDir) {
            step(60);
        }
    } else {
        setDir(backward);
        for (; digitalRead(endSwitchPin) == LOW; cartPos += currentDir) {
            step(60);
        }
        setDir(forward);
        for (; cartPos < 1000; cartPos += currentDir) {
            step(60);
        }
    }
}
