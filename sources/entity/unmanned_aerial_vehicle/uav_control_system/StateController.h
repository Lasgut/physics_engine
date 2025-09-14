#define STATE_CONTROLLER_H
#ifdef STATE_CONTROLLER_H

#pragma once

#include <Eigen/Dense>
#include "EntityStates.h"
#include "ControllerLib.h"

class StateController
{
    public:
        StateController() = default;

    protected:
        Eigen::Vector<double,6> computeDesiredControlWrench(EntityStates& errorStates);

    private:
        Lib::Controller::PID pitchController_{8, 0.1, 0, 0.2};
        Lib::Controller::PID velocityController_{4, 1, 0, 2};
};

#endif