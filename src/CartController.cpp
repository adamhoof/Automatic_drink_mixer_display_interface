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
    if (dir == forward) {currentDir = 1;}
    else if (dir == backward) {currentDir = -1;}
    else {return;}
}

void CartController::step() {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(60);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(60);
}

void CartController::moveToPos(int8_t pos) {
    if (pos != initPos) {
        setDir(forward);
        for (; cartPos < stationPositions[pos]; cartPos+=currentDir) {
            step();

        }
    } else {
        setDir(backward);
        while (!digitalRead(endSwitchPin)) {
            step();
            cartPos += currentDir;
        }

        setDir(forward);
        for (; cartPos < 2000; cartPos+=currentDir) {
            step();
        }
    }
}
