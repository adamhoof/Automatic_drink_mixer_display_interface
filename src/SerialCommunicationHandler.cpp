#include "SerialCommunicationHandler.h"

SoftwareSerial Ard_Display_Serial(2,3);

SerialCommunicationHandler::SerialCommunicationHandler() = default;

void SerialCommunicationHandler::setup() const //request communication on demand
{
  Serial.begin(baudRate);
  Ard_Display_Serial.begin(baudRate);
}

uint8_t* SerialCommunicationHandler::getDrinkContentChanges()
{
  static uint8_t dataBuffer[contentsBuffLen];

  if (!Ard_Display_Serial.available()){

    return nullptr; //return dataBuffer
  }

  Ard_Display_Serial.readBytes(dataBuffer, contentsBuffLen);
  return dataBuffer;
}

uint8_t* SerialCommunicationHandler::getElementIds()
{
  Ard_Display_Serial.print("page 2");

  for (int i = 0; i < 3 ; ++i) {

    Ard_Display_Serial.write(0xFF);
  }
  delay(10);

  static uint8_t dataBuffer[elemIdBuffLen];

  if (!Ard_Display_Serial.available()){

    return nullptr; //return dataBuffer
  }

  Ard_Display_Serial.readBytes(dataBuffer, elemIdBuffLen);
  return dataBuffer;
}

void SerialCommunicationHandler::updateDisplayProgressBar()
{
  Ard_Display_Serial.print("progressBar.val+=1");
  for (int i = 0; i < 3 ; ++i) {

    Ard_Display_Serial.write(0xFF);
  }
  delay(10);
}