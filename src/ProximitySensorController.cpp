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
    return pulse*0.034/2;
}

double ProximitySensorController::getProximity() {
    return convertPulseToCm(sendPulses());
}
