#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#define contentsBuffLen 2
#define elemIdBuffLen 7

class SerialCommunicationHandler
{
private:
  const int baudRate{9600};
public:
  SerialCommunicationHandler();
  void setup() const;
  uint8_t* getDrinkContentChanges();
  uint8_t* getElementIds();
  static void updateDisplayProgressBar();
};
