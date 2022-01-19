#include <Arduino.h>
#include <Servo.h>

class SyrupDispensers
{
private:
    Servo servo {11};
    Servo servo1 {10};
    Servo servo2 {9};
    Servo servo3 {6};
    Servo* dispensers[4];
    const uint8_t pins[4];
public:
    SyrupDispensers();

    void setup();

    void openValve(uint8_t dispenserIndex);

    void closeValve(uint8_t dispenser);
};
