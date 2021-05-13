#pragma once

#include <Arduino.h>
#include "SerialCommunicationHandler.h"

class DrinkContentsModifier {
public:
  uint8_t drinkContents;
  uint8_t elementIds[elemIdBuffLen];
public:
  DrinkContentsModifier();

  void modifyContents(const uint8_t *valueToModify);

  void setElementIds(const uint8_t* elementIds);
};

