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
    Serial.println("Calib sequence");
    setDir(backward);

    while (!isInitPos()) {
        step(cart.stepDelay);
    }
    for (int i = 0; i < 100; ++i) {
        step(cart.stepDelay);
    }

    unsigned long lastTimeMessured = millis();
    Serial.println("Should have hit switch");
    Serial.println(millis());
    Serial.println(lastTimeMessured);
    blockMovement();
    while (isInitPos()) {
        if (millis() - lastTimeMessured > validatingPeriod) {
            Serial.println("Should end counting");
            break;
        } else {
            Serial.println(millis());
        }
    }
    allowMovement();
    Serial.println("Init calib check");
    setDir(forward);
    moveToPos(calibValidatePos, forward);
    Serial.println(cart.pos);
    setDir(backward);
    moveToPos(initPos, backward);
    Serial.println(cart.pos);
    for (int i = 0; i < 100; ++i) {
        step(cart.stepDelay);
    }
    if (isInitPos()) {
        Serial.println("Calibration valid");
        setDir(forward);
        moveToPos(calibValidatePos, forward);
        return;
    }
    Serial.println("calibrate again");
}

void CartController::step(uint8_t stpDelay) {
    digitalWrite(cart.stepPin, HIGH);
    delayMicroseconds(stpDelay);
    digitalWrite(cart.stepPin, LOW);
    delayMicroseconds(stpDelay);
}

void CartController::moveToPos(const int32_t targetPos, bool dir) {
    if (dir == forward){
        for (; cart.pos < targetPos; cart.pos += cart.dir) {
            step(cart.stepDelay);
        }
    } else if (dir == backward){
        for (; cart.pos > targetPos; cart.pos += cart.dir) {
            step(cart.stepDelay);
        }
    }

}

bool CartController::isInitPos() const {
    return digitalRead(cart.endSwitchPin);
}

void CartController::blockMovement() const {
    digitalWrite(cart.motorEnablePin, LOW);
}

void CartController::allowMovement() const {
    digitalWrite(cart.motorEnablePin, HIGH);
}

