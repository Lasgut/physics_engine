#define STATE_CONTROLLER_H
#ifdef STATE_CONTROLLER_H

#pragma once

#include <Eigen/Dense>
#include "EntityStates.h"

class StateController
{
    public:
        StateController() = default;

    protected:
        Eigen::Vector<double,6> computeDesiredControlWrench(EntityStates& errorStates);
};

#endif