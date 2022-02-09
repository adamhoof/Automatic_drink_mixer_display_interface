#include "ProximitySensorController.h"

void ProximitySensorController::setup()
{
    pinMode(proximitySensor.echoPin, INPUT);
    pinMode(proximitySensor.trigPin, OUTPUT);
}

unsigned long ProximitySensorController::sendPulse()
{
    digitalWrite(proximitySensor.trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(proximitySensor.trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(proximitySensor.trigPin, LOW);
    return pulseIn(proximitySensor.echoPin, HIGH);
}

double ProximitySensorController::convertPulseToCm(unsigned long pulse)
{
    return pulse * 0.034 / 2;
}

double ProximitySensorController::getProximity()
{
    return convertPulseToCm(sendPulse());
}

bool ProximitySensorController::objectIsPresent(uint8_t numOfSamples)
{
    uint8_t medianIndex;

    if (numOfSamples % 2 == 0) {
        medianIndex = (numOfSamples) / 2;
    } else {
        medianIndex = (numOfSamples + 1) / 2;
    }

    double proximitySamples[numOfSamples];

#define samplesMedian proximitySamples[medianIndex]

    for (double& proximity: proximitySamples) {
        proximity = getProximity();
        delay(10);
    }
    ace_sorting::shellSortKnuth(proximitySamples, numOfSamples);

    if (samplesMedian > 0 && samplesMedian < 9.5) {
        return true;
    } else if (samplesMedian > 9.5 && samplesMedian < 900) {
        return false;
    }
    return false;
}
