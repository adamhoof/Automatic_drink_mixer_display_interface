#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

class SerialCommunicationHandler
{
private:
  const int baudRate = 9600;
public:
  SerialCommunicationHandler();

  void setup() const;

  uint8_t* gatherDisplayInputData();
};
