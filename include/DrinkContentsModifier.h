#pragma once

#include <Arduino.h>

class DrinkContentsModifier {
public:
  uint8_t drinkContents;
  uint8_t elementIds[5];
public:
  DrinkContentsModifier();

  void modifyContents(const uint8_t *valueToModify);

  void setElementIds(const uint8_t* elementIds);
};

