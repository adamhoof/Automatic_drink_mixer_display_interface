#include "ProximitySensorController.h"

void ProximitySensorController::init() {
    pinMode(proximitySensor.echoPin, INPUT);
    pinMode(proximitySensor.trigPin, OUTPUT);
}

unsigned long ProximitySensorController::sendPulses() {
    digitalWrite(proximitySensor.trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(proximitySensor.trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(proximitySensor.trigPin, LOW);
    return pulseIn(proximitySensor.echoPin, HIGH);
}

double ProximitySensorController::convertPulseToCm(unsigned long pulse) {
    return pulse * 0.034 / 2;
}

double ProximitySensorController::getProximity() {
    return convertPulseToCm(sendPulses());
}

bool ProximitySensorController::objectIsPresent() {
    const uint8_t validationSamplesSize = 31;
    const uint8_t median = (validationSamplesSize + 1) / 2;
    double proximityValidationSamples[validationSamplesSize];
#define samplesMedian proximityValidationSamples[median]

    for (double &proximity: proximityValidationSamples) {
        proximity = getProximity();
        delay(10);
    }
    ace_sorting::shellSortKnuth(proximityValidationSamples, validationSamplesSize);

    if (samplesMedian > 0 && samplesMedian < 9.5) {
        return true;
    } else if (samplesMedian > 9.5 && samplesMedian < 900) {
        return false;
    } else {
        return false;
    }
}
