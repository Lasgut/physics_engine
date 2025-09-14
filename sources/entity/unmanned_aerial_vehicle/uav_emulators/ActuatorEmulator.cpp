#include "ActuatorEmulator.h"


Eigen::Vector<double, 6> 
ActuatorEmulator::emulateActuatorDynamics(ActuatorStates &desiredStates)
{
    Eigen::Vector<double, 6> controlWrench(0,0,0,0,0,0);

    controlWrench[0] = desiredStates.getThrottle() * 20;
    controlWrench[3] = desiredStates.getAileron()  * 0.5;
    controlWrench[4] = desiredStates.getElevator() * 0.7;

    return controlWrench;
}
