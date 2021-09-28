#pragma once

#include <Arduino.h>
#include <HX711_ADC.h>

const uint8_t doutPin{3};
const uint8_t sckPin{2};
const float calibrationValue{731.43};
const uint16_t stabilizingTime{100};
const bool doTare{true};
