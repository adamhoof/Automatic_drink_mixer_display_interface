#include <Arduino.h>
#include "SerialCommunicationHandler.h"
#include "DrinkStateController.h"


SerialCommunicationHandler serialCommunicationHandler;
DrinkStateController drinkContentModifier;

void setup()
{
  serialCommunicationHandler.setup();
}

void loop()
{
  drinkContentModifier.modifyState(serialCommunicationHandler.gatherDisplayInputData());
}
