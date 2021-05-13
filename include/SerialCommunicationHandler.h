#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#define contentsBuffLen 2
#define ElemIdBuffLen 5

class SerialCommunicationHandler
{
private:
  const int baudRate = 9600;
public:
  uint8_t sField_elementIdArray[ElemIdBuffLen];
public:
  SerialCommunicationHandler();

  void setup() const;

  uint8_t*getDrinkContentsData();

  uint8_t*getElementIds();
};
