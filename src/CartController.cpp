#include "CartController.h"

CartController::CartController() = default;

void CartController::setupControlPins(uint8_t motorEnPin, uint8_t dirPin, uint8_t stepPin, uint8_t endSwitchPin)
{
    cart.motorEnablePin = motorEnPin;
    cart.dirPin = dirPin;
    cart.stepPin = stepPin;
    cart.endSwitchPin = endSwitchPin;

    pinMode(cart.motorEnablePin, OUTPUT);
    pinMode(cart.dirPin, OUTPUT);
    pinMode(cart.stepPin, OUTPUT);
    pinMode(cart.endSwitchPin, INPUT);
}

void CartController::setStepDelay(const uint8_t& stepDel)
{
    cart.stepDelay = stepDel;
}

void CartController::setDir(const bool& dir)
{
    digitalWrite(cart.dirPin, dir);
    if (dir == forward) {
        cart.dir = 1;
    } else if (dir == backward) {
        cart.dir = -1;
    } else {
        return;
    }
}

void CartController::calibrate()
{
    rerunCalib:; // recursive function call ended up somehow runing multiple
    // functions at once, use goto instead:(
    allowMovement();
    while (!isInitPos()) {
        move();
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
    moveToPos(calibValidate, forward);
    blockMovement();
    while (isInitPos()) {
        // todo vypsat na display ze ma pustit switch
    }
    allowMovement();
    moveToPos(start, backward);
    correctFalseInitPos();
    if (isInitPos()) {
        setDir(forward);
        moveToPos(calibValidate, forward);
        return;
    }
    goto rerunCalib;
}

void CartController::move() const
{
    digitalWrite(cart.stepPin, HIGH);
    delayMicroseconds(cart.stepDelay);
    digitalWrite(cart.stepPin, LOW);
    delayMicroseconds(cart.stepDelay);
}

void CartController::moveToPos(const int32_t& targetPos, const bool& dir)
{
    if (dir == forward) {
        setDir(forward);
        for (; cart.pos < targetPos; cart.pos += cart.dir) {
            move();
        }
    } else if (dir == backward) {
        setDir(backward);
        for (; cart.pos > targetPos; cart.pos += cart.dir) {
            move();
        }
    }
}

void CartController::correctFalseInitPos() const
{
    for (int i = 0; i < 100; ++i) {
        move();
    }
}

bool CartController::isInitPos() const
{
    return digitalRead(cart.endSwitchPin);
}

void CartController::blockMovement() const
{
    digitalWrite(cart.motorEnablePin, LOW);
}

void CartController::allowMovement() const
{
    digitalWrite(cart.motorEnablePin, HIGH);
}
