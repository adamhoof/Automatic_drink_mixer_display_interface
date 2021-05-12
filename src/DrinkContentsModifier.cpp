#include "DrinkContentsModifier.h"

DrinkContentsModifier::DrinkContentsModifier()
    : drinkContents(B10000000) //for 16bit storage, can use 32768 as initial value - MSB of uint16_t set to 1 (only for nice bit reading in BIN, shows all the digits, not necessary)
{}

void DrinkContentsModifier::modifyContents(const uint8_t *valueToModify)
{
  switch (valueToModify[0]) {

  case 1:
    bitWrite(drinkContents, 0, valueToModify[1]);
    break;

  case 2:
    bitWrite(drinkContents, 1, valueToModify[1]);
    break;

  case 3:
    bitWrite(drinkContents, 2, valueToModify[1]);
    break;

  case 4:
    bitWrite(drinkContents, 3, valueToModify[1]);
    break;

  case 5:
    bitWrite(drinkContents, 4, valueToModify[1]);
    break;

  case 6:
    bitWrite(drinkContents, 5, valueToModify[1]);
    break;

  case 7:
    bitWrite(drinkContents, 6, 1);
    break;

  default:
    break;
  }
}
