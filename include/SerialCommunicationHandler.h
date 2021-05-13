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
  SerialCommunicationHandler();

  void setup() const;

  uint8_t*getDrinkContents();

  uint8_t*getElementIds();
};
