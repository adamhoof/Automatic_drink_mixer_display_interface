#include "DrinkContentsModifier.h"
#include "SerialCommunicationHandler.h"
#include <Arduino.h>

SerialCommunicationHandler serialCommunicationHandler;
DrinkContentsModifier drinkContentModifier;

void setup()
{
  serialCommunicationHandler.setup();
}

void loop()
{
  drinkContentModifier.modifyContents(serialCommunicationHandler.gatherDisplayInputData());
  Serial.println(drinkContentModifier.drinkContents, BIN);
}
