#ifndef ACTUATOR_EMULATOR_H
#define ACTUATOR_EMULATOR_H

#pragma once

#include <Eigen/Dense>
#include "uav_data_types/ActuatorStates.h"

namespace UAV
{
class ActuatorEmulator
{
    public:
        ActuatorEmulator() = default;

    protected:
        Eigen::Vector<double, 6> emulateActuatorDynamics(ActuatorStates& desiredStates);
};
}

#endif