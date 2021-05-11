#pragma once

#include <Arduino.h>

class DrinkStateController
{
public:
  uint8_t drinkContents;
public:
  DrinkStateController();

  void modifyState(const uint8_t valueToModify [2]);
};