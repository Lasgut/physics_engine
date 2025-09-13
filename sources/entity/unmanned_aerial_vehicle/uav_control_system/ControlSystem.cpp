#include "ControlSystem.h"

ActuatorStates 
ControlSystem::iterateControlLoop(SensorData& sensorData)
{
    if (!clock_.rateLimit(10)) // sensor sampling time
    {
        return actuatorInput_;
    }

    auto estimatedStates = estimateStates(sensorData);

    // Compute error states
    EntityStates errorStates;
    errorStates.velocity[0] = 10 - estimatedStates.velocity[0]; // Target speed is 10 m/s

    auto controlWrench = computeDesiredControlWrench(errorStates);
    actuatorInput_     = allocateActuators(controlWrench);

    return actuatorInput_;
}