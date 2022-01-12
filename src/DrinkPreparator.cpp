#include <DrinkPreparator.h>

DrinkPreparator::DrinkPreparator()
        : drinkContents(B10000000),
          drinkContentsPtr(&drinkContents)
{}

void DrinkPreparator::setDrinkContent(const uint8_t* receivedIdAndValue) const
{
    uint8_t receivedId = receivedIdAndValue[idPos];
    uint8_t receivedValue = receivedIdAndValue[valPos];
    delete receivedIdAndValue;

    switch (receivedId) {
        case idCancelButton:
            *drinkContentsPtr = B10000000;
            break;
        case idA:
            bitWrite(*drinkContentsPtr, idA, receivedValue);
            break;
        case idB:
            bitWrite(*drinkContentsPtr, idB, receivedValue);
            break;
        case idC:
            bitWrite(*drinkContentsPtr, idC, receivedValue);
            break;
        case idD:
            bitWrite(*drinkContentsPtr, idD, receivedValue);
            break;
        case idWater:
            bitWrite(*drinkContentsPtr, idWater, receivedValue);
            break;
        case idMakeDrinkButton:
            bitWrite(*drinkContentsPtr, idMakeDrinkButton, 0);
            break;
        default:
            break;
    }
}

bool DrinkPreparator::readyToProceed() const
{
    return !bitRead(*drinkContentsPtr, idMakeDrinkButton);
}
