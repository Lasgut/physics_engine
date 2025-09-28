#ifndef ACTUATOR_ALLOCATION_H
#define ACTUATOR_ALLOCATION_H

#pragma once

#include <Eigen/Dense>
#include "uav_data_types/ActuatorStates.h"

namespace UAV
{
class ActuatorAllocation
{
    public:
        ActuatorAllocation() = default;

    protected:
        ActuatorStates allocateActuators(const Eigen::Vector<double,6>& desiredControlWrench);
};
}

#endif