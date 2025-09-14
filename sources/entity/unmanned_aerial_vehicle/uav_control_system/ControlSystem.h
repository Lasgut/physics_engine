#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#pragma once

#include "StateEstimator.h"
#include "OperationController.h"
#include "StateEstimator.h"
#include "ActuatorAllocation.h"
#include "uav_data_types/ActuatorStates.h"
#include "uav_data_types/SensorData.h"
#include "Clock.h"

class ControlSystem
    : public OperationController
    , public StateEstimator
    , public ActuatorAllocation
{
    public:
        ControlSystem() = default;

    protected:
        ActuatorStates iterateControlLoop(SensorData& sensorData);

    private:
        ActuatorStates       actuatorInput_{};
        Clock                clock_;
        Clock                clockAltitude_; 
        Clock                clockDebug_;

        double desiredPitch_{0.0};
        Lib::Controller::PID altitudeController_{0.0001, 0.0002, 0, 0.05};

};

#endif