#include "StateController.h"
#include <iostream>


Eigen::Vector<double, 6> 
StateController::computeDesiredControlWrench(EntityStates &errorStates)
{
    Eigen::Vector<double, 6> desiredControlWrench(0,0,0,0,0,0);

    desiredControlWrench[0] = 1 * errorStates.velocity[0]; // velocityControl

    std::cout << "DEBUG: computeDesiredControlWrench: " << desiredControlWrench[0] << std::endl;
    
    return desiredControlWrench;
}
