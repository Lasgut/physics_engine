#ifndef STATE_ESTIMATOR_H
#define STATE_ESTIMATOR_H

#pragma once

#include "uav_data_types/SensorData.h"
#include "EntityStates.h"

class StateEstimator
{
    public:
        StateEstimator() = default;

    protected:
        EntityStates estimateStates(SensorData& sensorData);
};

#endif