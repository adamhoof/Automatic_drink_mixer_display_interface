#include "SerialCommunicationHandler.h"

SoftwareSerial Ard_Display_Serial(2,3);

SerialCommunicationHandler::SerialCommunicationHandler() = default;

void SerialCommunicationHandler::setup() const
{
  Serial.begin(baudRate);
  Ard_Display_Serial.begin(baudRate);
}

void SerialCommunicationHandler::gatherDisplayInputData()
{
  const uint8_t bufferLength = 2;
  uint8_t inputDataBuffer[bufferLength];

  if (!Ard_Display_Serial.available()){return;}

  else {
      Ard_Display_Serial.readBytes(inputDataBuffer, bufferLength);
  }

    Serial.println(inputDataBuffer[0]);
    Serial.println(inputDataBuffer[1]);
}
