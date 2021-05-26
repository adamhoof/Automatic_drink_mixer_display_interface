#include "DrinkPreparator.h"
#include "SerialCommunicationHandler.h"
#include <Arduino.h>

SerialCommunicationHandler serialCommunicationHandler;
DrinkPreparator drinkPreparator;

void setup()
{
  serialCommunicationHandler.setup();
  drinkPreparator.setElementIds(serialCommunicationHandler.getElementIds());
}

void loop()
{
  while (!bitRead(drinkPreparator.drinkContents, 6)){

    drinkPreparator.modifyContents(
        serialCommunicationHandler.getDrinkContentChanges());
    Serial.println(drinkPreparator.drinkContents, BIN);
  }

  SerialCommunicationHandler::updateDisplayProgressBar();
  delay(200);
}
