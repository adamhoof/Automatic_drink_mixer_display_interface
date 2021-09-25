#include "ProximitySensorController.h"

void ProximitySensorController::init() {
    pinMode(proximitySensor.echoPin, INPUT);
    pinMode(proximitySensor.trigPin, OUTPUT);
}

unsigned long ProximitySensorController::sendPulses() {
    digitalWrite(proximitySensor.trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(proximitySensor.trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(proximitySensor.trigPin, LOW);
    return pulseIn(proximitySensor.echoPin, HIGH);
}

double ProximitySensorController::convertPulseToCm(unsigned long pulse) {
    return ((double)pulse/2)/29.1;
}

double ProximitySensorController::getProximity() {
    return convertPulseToCm(sendPulses());
}
