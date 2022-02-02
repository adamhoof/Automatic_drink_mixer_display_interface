#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#define contentsBuffLen 2
#define placeObjectPage "page pPlaceObj"
#define initPage "page pInit"
#define initTextField "initTxt"
#define initProgressBar "initProgress"
#define createDrinkPage "page pCreateDrink"

class DisplayInterfaceHandler
{
private:
    const int baudRate {9600};
    const uint8_t receivePin {12};
    const uint8_t transmitPin {8};
public:
    DisplayInterfaceHandler();

    SoftwareSerial ardDisplaySerial {receivePin, transmitPin};

    void setup();

    uint8_t* getContentUpdate();

    void changePage(const String& page);

    void writeUselessBytes();

    void updateProgressBar(const String& progressBar, const String& valueToAdd);

    void updateTextField(const String& textField, const String& value);
};
