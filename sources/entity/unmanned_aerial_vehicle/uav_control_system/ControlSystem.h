#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#pragma once

#include "StateEstimator.h"
#include "OperationController.h"
#include "StateEstimator.h"
#include "ActuatorAllocation.h"
#include "uav_data_types/ActuatorStates.h"
#include "uav_data_types/SensorData.h"
#include "uav_data_types/ControlSystemData.h"
#include "Clock.h"

namespace UAV
{
class ControlSystem
    : public OperationController
    , public StateEstimator
    , public ActuatorAllocation
{
    public:
        ControlSystem() = default;
        
        ControlSystemData& getControlSystemData();

    protected:
        void iterateControlLoop(SensorData& sensorData);
        ActuatorStates& getDesiredActuatorStates();

    private:
        std::mutex           actuatorMtx_;
        ActuatorStates       actuatorInput_{};
        Clock                clock_{"ControlSystem"};
        Clock                clockAltitude_{"altitudeControl"}; 
        Clock                clockDebug_;

        ControlSystemData controlSystemData_;
        Lib::Controller::PID altitudeController_{0.1, 0, 0, 0};

};
}

#endif