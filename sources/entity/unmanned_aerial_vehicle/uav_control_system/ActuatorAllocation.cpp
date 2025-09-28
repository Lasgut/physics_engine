#include "ActuatorAllocation.h"
#include "math/utilities.h"

namespace UAV
{
ActuatorStates 
ActuatorAllocation::allocateActuators(const Eigen::Vector<double,6>& desiredControlWrench)
{
    ActuatorStates actuatorInput{};

    actuatorInput.setThrottle(desiredControlWrench[0] / 20);    
    actuatorInput.setElevator(desiredControlWrench[4] / 0.7);  // Scale factor for elevator
    actuatorInput.setAileron(desiredControlWrench[3] / 0.5);  // Not used in this simple model

    return actuatorInput;
}
}
