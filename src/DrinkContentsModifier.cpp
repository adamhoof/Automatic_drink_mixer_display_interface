#include "DrinkContentsModifier.h"
#include "SerialCommunicationHandler.h"

DrinkContentsModifier::DrinkContentsModifier()
    : drinkContents(B10000000),
      elementIds {}//for 16bit storage, can use 32768 as initial value - MSB of uint16_t set to 1 (only for nice bit reading in BIN, shows all the digits, not necessary)
{}

void DrinkContentsModifier::modifyContents(const uint8_t *valueToModify)
{
  if (valueToModify [0] == elementIds [0]) {

    bitWrite(drinkContents, 0, valueToModify[1]);

  } else if (valueToModify [0] == elementIds [1]) {

    bitWrite(drinkContents, 1, valueToModify[1]);

  } else if (valueToModify [0] == elementIds [2]) {

    bitWrite(drinkContents, 2, valueToModify[1]);

  } else if (valueToModify [0] == elementIds [3]) {

    bitWrite(drinkContents, 3, valueToModify[1]);

  } else if (valueToModify [0] == elementIds [4]) {

    bitWrite(drinkContents, 4, valueToModify[1]);
  }
}

void DrinkContentsModifier::setElementIds(const uint8_t *receivedElemIds)
{
  for (int i = 0; i < ElemIdBuffLen; ++i) {
    elementIds[i] = receivedElemIds[i];
  }
}
