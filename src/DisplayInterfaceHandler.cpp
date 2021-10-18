#include "DisplayInterfaceHandler.h"

DisplayInterfaceHandler::DisplayInterfaceHandler() = default;

struct DataBuffers
{
    static uint8_t drinkContentBuffer[contentsBuffLen];
    static uint8_t elementIDBuffer[elemIdBuffLen];
};

void DisplayInterfaceHandler::init() //request communication on demand
{
    ardDisplaySerial.begin(baudRate);
}

uint8_t* DisplayInterfaceHandler::getDrinkData()
{
    if (!ardDisplaySerial.available()) {
        return nullptr;
    }

    ardDisplaySerial.readBytes(DataBuffers::drinkContentBuffer, contentsBuffLen);
    return DataBuffers::drinkContentBuffer;
}

uint8_t* DisplayInterfaceHandler::getElementIds()
{
    ardDisplaySerial.print("page 2");
    for (int i = 0; i < 3; ++i) {

        ardDisplaySerial.write(0xFF);
    }
    delay(10);


    if (!ardDisplaySerial.available()) {
        return nullptr; //return dataBuffer
    }

    ardDisplaySerial.readBytes(DataBuffers::elementIDBuffer, elemIdBuffLen);
    return DataBuffers::elementIDBuffer;
}
