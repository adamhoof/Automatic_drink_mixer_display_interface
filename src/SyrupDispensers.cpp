#include "SyrupDispensers.h"

SyrupDispensers::SyrupDispensers() : dispensers {&servo, &servo1, &servo2, &servo3}, pins {11, 10, 9, 6}
{}

void SyrupDispensers::setup()
{
    for (int dispenserIndex = 0; dispenserIndex < 4; ++dispenserIndex) {
        dispensers[dispenserIndex]->attach(pins[dispenserIndex]);
        dispensers[dispenserIndex]->write(fullyClosed);
    }
}

void SyrupDispensers::open(uint8_t dispenserIndex)
{
    for (int pos = fullyClosed; pos < fullyOpen; ++pos) {
        dispensers[dispenserIndex]->write(pos);
        delay(5);
    }
}

void SyrupDispensers::close(uint8_t dispenserIndex)
{
    for (int pos = fullyOpen; pos > fullyClosed; --pos) {
        dispensers[dispenserIndex]->write(pos);
        delay(5);
    }
}

void SyrupDispensers::refill(uint8_t dispenserIndex) //sometimes, after dispensing syrup, it did not refill automatically, but the 35ml syrup container stood empty.
{                                                   // this function prevents that behavior, so the container is always filled up with new syrup
    for (int pos = fullyClosed; pos < refillPos; ++pos) {
        dispensers[dispenserIndex]->write(pos);
        delay(5);
    }
    close(dispenserIndex);
}
