#include "DrinkStateController.h"


DrinkStateController::DrinkStateController()
    : drinkContents(B10000000) //for 16bit storage, can use 32768 as initial value - MSB of uint16_t set to 1 (only for nice bit reading in BIN, shows all the digits, not necessary)
{}

void DrinkStateController::modifyState(const uint8_t valueToModify [2])
{
  switch (valueToModify[0]) {

  case 0:
    bitWrite(drinkContents, 3, valueToModify[1]);
    break;

  case 1:
    bitWrite(drinkContents, 2, valueToModify[1]);
    break;

  case 2:
    bitWrite(drinkContents, 1, valueToModify[1]);
    break;

  case 3:
    bitWrite(drinkContents, 0, valueToModify[1]);
    break;

  default:
    break;
  }
}
