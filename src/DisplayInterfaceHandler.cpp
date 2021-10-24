#include "DisplayInterfaceHandler.h"

DisplayInterfaceHandler::DisplayInterfaceHandler() = default;

void DisplayInterfaceHandler::init()
{
    ardDisplaySerial.begin(baudRate);

    ardDisplaySerial.print("page pStart");

    for (int i = 0; i < 3 ; ++i) {

        ardDisplaySerial.write(0xFF);
    }
}

uint8_t* DisplayInterfaceHandler::getDrinkData()
{
    static uint8_t dataBuffer[contentsBuffLen];

    if (!ardDisplaySerial.available()){

        return nullptr; //return dataBuffer
    }

    ardDisplaySerial.readBytes(dataBuffer, contentsBuffLen);
    return dataBuffer;
}
