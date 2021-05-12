#include "SerialCommunicationHandler.h"

SoftwareSerial Ard_Display_Serial(2,3);

SerialCommunicationHandler::SerialCommunicationHandler() = default;

void SerialCommunicationHandler::setup() const
{
  Serial.begin(baudRate);
  Ard_Display_Serial.begin(baudRate);
}

uint8_t* SerialCommunicationHandler::gatherDisplayInputData()
{
  const uint8_t bufferLength = 2;
  static uint8_t inputDataBuffer[bufferLength];

  if (Ard_Display_Serial.available()){

    Ard_Display_Serial.readBytes(inputDataBuffer, bufferLength);
    return inputDataBuffer;
  }
  return nullptr;
}
