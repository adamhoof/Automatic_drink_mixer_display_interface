#include "SerialCommunicationHandler.h"

SoftwareSerial Ard_Display_Serial(2,3);

SerialCommunicationHandler::SerialCommunicationHandler() = default;

void SerialCommunicationHandler::setup() const
{
  Serial.begin(baudRate);
  Ard_Display_Serial.begin(baudRate);
}

uint8_t* SerialCommunicationHandler::getDrinkContents()
{
  static uint8_t dataBuffer[contentsBuffLen];

  if (Ard_Display_Serial.available()){

    Ard_Display_Serial.readBytes(dataBuffer, contentsBuffLen);
    return dataBuffer;
  }
  return nullptr;
}

uint8_t* SerialCommunicationHandler::getElementIds()
{
  Ard_Display_Serial.print("page 2");
  Ard_Display_Serial.write(0xFF);
  Ard_Display_Serial.write(0xFF);
  Ard_Display_Serial.write(0xFF);
  delay(10);

  static uint8_t dataBuffer[ElemIdBuffLen];

  if (Ard_Display_Serial.available()){

    Ard_Display_Serial.readBytes(dataBuffer, ElemIdBuffLen);
    return dataBuffer;
  }
  return nullptr;
}
