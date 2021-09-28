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
    //todo simplify calib code, remove firt part, improve second
    rerunCalib:; //recursive function call ended up somehow runing multiple functions at once, use goto instead:(
    Serial.println("Calib sequence");
    allowMovement();
    while (!isInitPos()) {
        move(cart.stepDelay);
    }
    correctFalseInitPos();
    blockMovement();
    unsigned long lastTimeMessured = millis();
    while (millis() - lastTimeMessured < validatingPeriod) {
        if (!isInitPos()) {
            goto rerunCalib;
        }
    }
    cart.pos = 0;
    allowMovement();
    moveToPos(positions::calibValidate, forward);
    blockMovement();
    while (isInitPos()) {
        //todo vypsat na display ze ma pustit switch
    }
    allowMovement();
    moveToPos(positions::start, backward);
    correctFalseInitPos();
    if (isInitPos()) {
        setDir(forward);
        moveToPos(positions::calibValidate, forward);
        return;
    }
    goto rerunCalib;
}

void CartController::move(uint8_t stpDelay) {
    digitalWrite(cart.stepPin, HIGH);
    delayMicroseconds(stpDelay);
    digitalWrite(cart.stepPin, LOW);
    delayMicroseconds(stpDelay);
}

void CartController::moveToPos(const int32_t targetPos, const bool dir) {
    if (dir == forward) {
        setDir(forward);
        for (; cart.pos < targetPos; cart.pos += cart.dir) {
            move(cart.stepDelay);
        }
    } else if (dir == backward) {
        setDir(backward);
        for (; cart.pos > targetPos; cart.pos += cart.dir) {
            move(cart.stepDelay);
        }
    }
}

void CartController::correctFalseInitPos() {
    for (int i = 0; i < 100; ++i) {
        move(cart.stepDelay);
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
