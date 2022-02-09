#include "DisplayInterfaceHandler.h"

DisplayInterfaceHandler::DisplayInterfaceHandler() = default;

void DisplayInterfaceHandler::changePage(const String& page)
{
    ardDisplaySerial.print(page);
    writeUselessBytes();
}

void DisplayInterfaceHandler::setup()
{
    ardDisplaySerial.begin(baudRate);
    delay(100);
    changePage(initPage);
}

uint8_t* DisplayInterfaceHandler::getContentUpdate()
{
    static uint8_t dataBuffer[contentsBuffLen];

    if (!ardDisplaySerial.available()) {
        return nullptr;
    }

    ardDisplaySerial.readBytes(dataBuffer, contentsBuffLen);
    return dataBuffer;
}

void DisplayInterfaceHandler::writeUselessBytes()
{
    for (int i = 0; i < 3; ++i) {
        ardDisplaySerial.write(0xFF);
    }
    delay(10);
};

void DisplayInterfaceHandler::updateProgressBar(const String& progressBar, const String& valueToAdd)
{
    ardDisplaySerial.print(progressBar + ".val+=" + valueToAdd);
    writeUselessBytes();
}

void DisplayInterfaceHandler::updateTextField(const String& textField, const String& value)
{
    ardDisplaySerial.print(textField + ".txt=" + "\"" + value + "\"");
    writeUselessBytes();
}
