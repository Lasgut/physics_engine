#include "CommandInputHandler.h"
#include "EventState.h"
#include <Eigen/Dense>

CommandInputHandler::CommandInputHandler()
{
    cmdStates_.position = Eigen::Vector3d(0,0,100); // Start at 100m altitude
}


void 
CommandInputHandler::processCommands()
{
    cmdControlWrench_.setZero();
    if (EventState::getInstance().keyboard.up)
        cmdStates_.position[2] += 1.0; // Pitch down
    if (EventState::getInstance().keyboard.down)
        cmdStates_.position[2] -= 1.0;  // Pitch up
    if (EventState::getInstance().keyboard.left)
        cmdControlWrench_[3] = -0.5; // Roll left
    if (EventState::getInstance().keyboard.right)
        cmdControlWrench_[3] = 0.5;  // Roll right
    if (EventState::getInstance().keyboard.space)
        cmdControlWrench_[2] = 2.0; // Thrust (optional for now)

}