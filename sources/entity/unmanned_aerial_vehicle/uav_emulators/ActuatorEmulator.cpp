#include "ActuatorEmulator.h"
#include <iostream>


Eigen::Vector<double, 6> 
ActuatorEmulator::emulateActuatorDynamics(ActuatorStates &desiredStates)
{
    Eigen::Vector<double, 6> controlForces(0,0,0,0,0,0);

    controlForces[0] = desiredStates.throttle * 10;

    std::cout << "DEBUG: emulateActuatorDynamics: " << controlForces[0] << std::endl;

    return controlForces;
}
