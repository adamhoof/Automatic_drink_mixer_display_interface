#pragma once

#include <Arduino.h>
#include "SerialCommunicationHandler.h"

class DrinkPreparator {
public:
  uint8_t drinkContents;
public:
  DrinkPreparator();

  struct ElementIds {uint8_t idA, idB, idC, idD, idWater, idCancelButton, idMakeDrinkButton; };

  void modifyContents(const uint8_t *receivedIdAndValue);

  void setElementIds(const uint8_t* elementIds);
};

