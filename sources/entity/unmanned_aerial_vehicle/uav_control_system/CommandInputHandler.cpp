#include "CommandInputHandler.h"
#include "EventState.h"

void 
CommandInputHandler::processCommand()
{
    // Eigen::Vector<double,6> controlForces(0,0,0,0,0,0);
    // Eigen::Vector3d         desiredRates(0, 0, 0); // [p_ref, q_ref, r_ref] (roll, pitch, yaw rates)

    // if (EventState::getInstance().keyboard.up)
    //     desiredRates[1] = -0.5; // Pitch down
    // if (EventState::getInstance().keyboard.down)
    //     desiredRates[1] = 0.5;  // Pitch up
    // if (EventState::getInstance().keyboard.left)
    //     desiredRates[0] = -0.5; // Roll left
    // if (EventState::getInstance().keyboard.right)
    //     desiredRates[0] = 0.5;  // Roll right
    // if (EventState::getInstance().keyboard.space)
    //     controlForces[0] = 2.0; // Thrust (optional for now)
    // else
    //     controlForces[0] = velocityController_.control(12, kinematics_.getVelocity()[0]);

    // // if (desiredRates[1] == 0)
    // //     desiredRates[1]= pitchController_.control(0.0, kinematics_.getEulerAngles()[1]);

    // controlForces[3] = rollRateController_.control(desiredRates[0], kinematics_.getAngularVelocity()[0]);
    // controlForces[4] = pitchRateController_.control(desiredRates[1], kinematics_.getAngularVelocity()[1]);
}