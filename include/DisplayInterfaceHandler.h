#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#define contentsBuffLen 2
#define elemIdBuffLen 7

class DisplayInterfaceHandler
{
private:
    const int baudRate {9600};
    const uint8_t receivePin {8};
    const uint8_t transmitPin {9};

public:
    DisplayInterfaceHandler();

    SoftwareSerial ardDisplaySerial {receivePin, transmitPin};

    void init();

    uint8_t* getDrinkData();

    uint8_t* getElementIds();

};
