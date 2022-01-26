#include "SyrupDispensers.h"

SyrupDispensers::SyrupDispensers() : dispensers {&servo, &servo1, &servo2, &servo3}, pins {11, 10, 9, 6}
{}

void SyrupDispensers::setup()
{
    for (int i = 0; i < 4; ++i) {
        dispensers[i]->attach(pins[i]);
        dispensers[i]->write(30);
    }
}

void SyrupDispensers::openValve(uint8_t dispenserIndex)
{
    for (int i = 30; i < 130; ++i) {
        dispensers[dispenserIndex]->write(i);
        delay(5);
    }
}

void SyrupDispensers::closeValve(uint8_t dispenser)
{
    for (int i = 130; i > 30; --i) {
        dispensers[dispenser]->write(i);
        delay(5);
    }
}
