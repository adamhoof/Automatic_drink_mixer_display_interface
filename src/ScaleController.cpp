#include "ScaleController.h"

ScaleController::ScaleController() = default;

void ScaleController::init()
{
    scale.begin();

    scale.start(stabilizingTime, doTare);
    if (scale.getTareTimeoutFlag()) {
        ScaleController::init();
    }
    scale.setCalFactor(calibrationValue);
}

float ScaleController::getWeight()
{
    for (int i = 0; i < 15000; ++i) {
        scale.update();
        scale.getData();
    }
    return scale.getData();
}
