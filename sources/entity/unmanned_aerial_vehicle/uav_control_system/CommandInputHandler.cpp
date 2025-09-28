#include "CommandInputHandler.h"
#include "EventState.h"
#include <Eigen/Dense>
#include <iostream>

namespace UAV
{
CommandInputHandler::CommandInputHandler()
{
    cmdStates_.position = Eigen::Vector3d(0,0,100); // Start at 100m altitude
}


void 
CommandInputHandler::processCommands()
{
    cmdControlWrench_.setZero();
    static bool upStillPressed = false;
    static bool downStillPressed = false;
    if (EventState::getInstance().keyboard.up && !upStillPressed)
    {
        cmdStates_.position[2] += 1.0; // altitude down
        upStillPressed = true;
    }
    if (!EventState::getInstance().keyboard.up)
    {
        upStillPressed = false;
    }
    if (EventState::getInstance().keyboard.down && !downStillPressed)
    {
        cmdStates_.position[2] -= 1.0;  // altitude up
        downStillPressed = true;
    }
    if (!EventState::getInstance().keyboard.down)
    {
        downStillPressed = false;
    }
    if (EventState::getInstance().keyboard.left)
        cmdControlWrench_[3] = -0.5; // Roll left
    if (EventState::getInstance().keyboard.right)
        cmdControlWrench_[3] = 0.5;  // Roll right
    if (EventState::getInstance().keyboard.space)
        cmdControlWrench_[2] = 2.0; // Thrust (optional for now)
}
}