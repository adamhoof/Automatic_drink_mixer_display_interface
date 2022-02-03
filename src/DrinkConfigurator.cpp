#include <DrinkConfigurator.h>

DrinkConfigurator::DrinkConfigurator()
        : contents {B10000000},
          contentsPtr {&contents}
{}

void DrinkConfigurator::resetContents() const
{
    *contentsPtr = B10000000;
}

void DrinkConfigurator::setContent(const uint8_t* receivedIdAndValue) const
{
    uint8_t receivedId = receivedIdAndValue[idPos];
    uint8_t receivedValue = receivedIdAndValue[valPos];
    delete receivedIdAndValue;

    switch (receivedId) {
        case idCancelButton:
            resetContents();
            break;
        case idA:
            bitWrite(*contentsPtr, idA, receivedValue);
            break;
        case idB:
            bitWrite(*contentsPtr, idB, receivedValue);
            break;
        case idC:
            bitWrite(*contentsPtr, idC, receivedValue);
            break;
        case idD:
            bitWrite(*contentsPtr, idD, receivedValue);
            break;
        case idWater:
            bitWrite(*contentsPtr, idWater, receivedValue);
            break;
        case idMakeDrinkButton:
            bitWrite(*contentsPtr, idMakeDrinkButton, 0);
            break;
        default:
            break;
    }
}

bool DrinkConfigurator::configurationComplete() const
{
    return !bitRead(*contentsPtr, idMakeDrinkButton);
}

uint8_t* DrinkConfigurator::getAllContents()
{
    return contentsPtr;
}
