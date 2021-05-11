#include <Arduino.h>
#include "SerialCommunicationHandler.h"

SerialCommunicationHandler serialCommunicationHandler;

void setup()
{
  serialCommunicationHandler.setup();
}

void loop()
{
  serialCommunicationHandler.gatherDisplayInputData();
}
