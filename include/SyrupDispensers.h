#include <Arduino.h>
#include <Servo.h>

class SyrupDispensers
{
private:
    Servo dispensers[4];
public:
    SyrupDispensers();

    void openValve(uint8_t dispenser);

    void closeValve(uint8_t dispenser);
};
