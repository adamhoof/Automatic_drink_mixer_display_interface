#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#define contentsBuffLen 2

class DisplayInterfaceHandler
{
private:
    const int baudRate {9600};
    const uint8_t receivePin {12};
    const uint8_t transmitPin {8};
    const String startPage{"page pStart"};

public:
    DisplayInterfaceHandler();

    SoftwareSerial ardDisplaySerial {receivePin, transmitPin};

    void setup();

    uint8_t* getDrinkData();

    void changePage(const String& page);

    void writeUselessBytes();
};
