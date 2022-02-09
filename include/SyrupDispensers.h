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
    const uint8_t fullyOpen {130};
    const uint8_t fullyClosed {30};
    const uint8_t refillPos{70};
public:
    SyrupDispensers();

    void setup();

    void open(uint8_t dispenserIndex);

    void close(uint8_t dispenserIndex);

    void refill(uint8_t dispenserIndex);

    void detach(uint8_t dispenserIndex);

    void attach(uint8_t dispenserIndex);
};
