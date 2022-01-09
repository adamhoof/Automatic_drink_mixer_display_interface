#include "SyrupDispensers.h"

SyrupDispensers::SyrupDispensers(): dispensers{Servo(11), Servo(10), Servo(9), Servo(6)}
{}

void SyrupDispensers::openValve(uint8_t dispenser)
{
    for (int i = 0; i < 130; ++i) {
        dispensers[dispenser].write(i);
        delay(5);
    }
}

void SyrupDispensers::closeValve(uint8_t dispenser)
{
    for (int i = 130; i < 0; --i) {
        dispensers[dispenser].write(i);
        delay(5);
    }
}


