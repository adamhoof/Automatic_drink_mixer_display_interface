#include "ScaleController.h"

ScaleController::ScaleController() = default;

void ScaleController::setup()
{
    scale.begin();

    failedSetup:
    scale.start(stabilizingTime, doTare);
    if (scale.getTareTimeoutFlag()) {
        goto failedSetup;
    }
    scale.setCalFactor(calibrationValue);
}

float ScaleController::getWeight()
{
    scale.update();
    for (int i = 0; i < 4000; ++i) {
        scale.update();
        scale.getData();
    }
    return scale.getData();
}

void ScaleController::tare(){
    scale.tare();
}
