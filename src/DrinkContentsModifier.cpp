#include "DrinkContentsModifier.h"

DrinkContentsModifier::DrinkContentsModifier()
    : m_drinkContents(B10000000),
      m_elementIds {}//for 16bit storage, can use 32768 as initial value - MSB of uint16_t set to 1 (only for nice bit reading in BIN, shows all the digits anytime, not necessary)
{}

void DrinkContentsModifier::modifyContents(const uint8_t *valueToModify)
{
  if (valueToModify [0] == m_elementIds [0]) {

    bitWrite(m_drinkContents, 0, valueToModify[1]); //A content

  } else if (valueToModify [0] == m_elementIds [1]) {

    bitWrite(m_drinkContents, 1, valueToModify[1]); //B content

  } else if (valueToModify [0] == m_elementIds [2]) {

    bitWrite(m_drinkContents, 2, valueToModify[1]); //C content

  } else if (valueToModify [0] == m_elementIds [3]) {

    bitWrite(m_drinkContents, 3, valueToModify[1]); //D content

  } else if (valueToModify [0] == m_elementIds [4]) {

    bitWrite(m_drinkContents, 4, valueToModify[1]); //water type

  } else if (valueToModify [0] == m_elementIds [5]) {

    m_drinkContents = B10000000; //cancel button pressed

  } else if (valueToModify [0] == m_elementIds [6]) {

    //continue button pressed
  }
}

void DrinkContentsModifier::setElementIds(const uint8_t *receivedElemIds)
{
  for (int i = 0; i < elemIdBuffLen; ++i) {
    m_elementIds[i] = receivedElemIds[i];
  }
}
