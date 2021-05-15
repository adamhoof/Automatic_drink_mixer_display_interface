#include "DrinkPreparator.h"
#include "SerialCommunicationHandler.h"
#include <Arduino.h>

SerialCommunicationHandler serialCommunicationHandler;
DrinkPreparator drinkContentModifier;

void setup()
{
  serialCommunicationHandler.setup();
  drinkContentModifier.setElementIds(serialCommunicationHandler.getElementIds());
}

void loop()
{
    drinkContentModifier.modifyContents(
      serialCommunicationHandler.getDrinkContentChanges());
    Serial.println(drinkContentModifier.drinkContents, BIN);
}
