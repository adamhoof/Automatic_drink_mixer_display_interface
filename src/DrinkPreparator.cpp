#include <DrinkPreparator.h>

DrinkPreparator::DrinkPreparator()
        : drinkContents(B10000000),
          drinkContentsPtr(&drinkContents)
{}

void DrinkPreparator::modifyContents(const uint8_t* receivedIdAndValue)
{
    uint8_t receivedId = receivedIdAndValue[idPos];
    uint8_t receivedValue = receivedIdAndValue[valPos];
    delete receivedIdAndValue;

    if (receivedId == idA) {
        bitWrite(*drinkContentsPtr, idA, receivedValue);

    } else if (receivedId == idB) {
        bitWrite(*drinkContentsPtr, idB, receivedValue);

    } else if (receivedId == idC) {
        bitWrite(*drinkContentsPtr, idC, receivedValue);

    } else if (receivedId == idD) {
        bitWrite(*drinkContentsPtr, idD, receivedValue);

    } else if (receivedId == idWater) {
        bitWrite(*drinkContentsPtr, idWater, receivedValue);

    } else if (receivedId == idCancelButton) {
        *drinkContentsPtr = B10000000;

    } else if (receivedId == idMakeDrinkButton) {
        bitWrite(*drinkContentsPtr, idMakeDrinkButton, 0);
    }
}

bool DrinkPreparator::readyToProceed() const
{
    return !bitRead(*drinkContentsPtr, idMakeDrinkButton);
}
