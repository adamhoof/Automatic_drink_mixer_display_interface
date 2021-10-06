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
    scale.update();
    return scale.getData();
}
