#pragma once

#include <Arduino.h>

class DrinkContentsModifier {
public:
  uint8_t drinkContents;
public:
  DrinkContentsModifier();

  void modifyContents(const uint8_t *valueToModify);
};