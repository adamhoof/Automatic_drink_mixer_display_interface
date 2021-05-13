#include "DrinkContentsModifier.h"
#include "SerialCommunicationHandler.h"
#include <Arduino.h>

SerialCommunicationHandler serialCommunicationHandler;
DrinkContentsModifier drinkContentModifier;

void setup()
{
  serialCommunicationHandler.setup();
  drinkContentModifier.setElementIds(serialCommunicationHandler.getElementIds());
}

void loop()
{
  drinkContentModifier.modifyContents(
      serialCommunicationHandler.getDrinkContents());
  Serial.println(drinkContentModifier.drinkContents, BIN);
}
