#include "CartController.h"

CartController::CartController() : positions {16000, 37500, 59000, 83000, 0, 1300},
                                   validatingPeriod {3000}
{}

void CartController::setup()
{
    pinMode(cart.motorEnablePin, OUTPUT);
    pinMode(cart.dirPin, OUTPUT);
    pinMode(cart.stepPin, OUTPUT);
    pinMode(cart.endSwitchPin, INPUT);
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
    rerunCalib:; // recursive function call ended up somehow running multiple
    // functions at once, use goto instead :(
    setDir(backward);
    allowMovement();
    while (!isInitPos()) {
        move();
    }
    fukDaSwitch();
    stopBullyingEndSwitch();
    blockMovement();
    unsigned long lastTimeMessured = millis();
    while (millis() - lastTimeMessured < validatingPeriod) {
        if (!isInitPos()) {
            goto rerunCalib;
        }
    }
    setPos(0);
    allowMovement();
    moveToPos(calibValidate, forward);
    blockMovement();

    while (isInitPos()) {} //wait until the switch is released

    allowMovement();
    moveToPos(startPos, backward);
    stopBullyingEndSwitch();
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

void CartController::moveToPos(uint8_t posIndex, const bool& dir)
{
    allowMovement();
    setDir(dir);
    if (dir == forward) {
        for (; cart.pos < positions[posIndex]; cart.pos += cart.dir) {
            move();
        }
    } else if (dir == backward) {
        for (; cart.pos > positions[posIndex]; cart.pos += cart.dir) {
            move();
        }
    }
    blockMovement();
}

void CartController::fukDaSwitch() const //ensures there are no false switch readings, results in cart just goin' crazy
{
    for (int i = 0; i < 120; ++i) {
        move();
    }
}

void CartController::stopBullyingEndSwitch() const //moves away from the switch so that it doesn't scream
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

void CartController::setPos(int32_t posToSet)
{
    cart.pos = posToSet;
}
