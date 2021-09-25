#include <ProximitySensorController.h>
#include <Arduino.h>

ProximitySensorController proximitySensorController{};

void setup() {
    Serial.begin(9600);
    proximitySensorController.init();
}

void loop() {
    Serial.println(proximitySensorController.getProximity());
    delay(500);
}


