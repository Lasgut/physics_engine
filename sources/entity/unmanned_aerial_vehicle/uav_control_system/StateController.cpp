#include "StateController.h"

namespace UAV
{
Eigen::Vector<double, 6> 
StateController::computeDesiredControlWrench(EntityStates &errorStates)
{
    Eigen::Vector<double, 6> desiredControlWrench(0,0,0,0,0,0);

    desiredControlWrench[0] = velocityController_.control(errorStates.velocity[0]); // velocityControl

    desiredControlWrench[4] = pitchController_.control(errorStates.eulerAngels[1]);     // pitchControl
    
    // double pitchTrim = 0.2; // Adjust this value based on hover conditions
    // desiredControlWrench[4] = pitchTrim + (0.8 * errorStates.pitch);     // pitchControl
    
    return desiredControlWrench;
}
}
