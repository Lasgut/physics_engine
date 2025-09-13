#include "ActuatorAllocation.h"
#include <iostream>


ActuatorStates 
ActuatorAllocation::allocateActuators(const Eigen::Vector<double,6>& desiredControlWrench)
{
    ActuatorStates actuatorInput{};

    actuatorInput.throttle = desiredControlWrench[0];

    std::cout << "DEBUG: allocateActuators: " << actuatorInput.throttle << std::endl;

    return actuatorInput;
}
