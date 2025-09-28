#define COMMAND_INPUT_HANDLER_H
#ifdef COMMAND_INPUT_HANDLER_H

#pragma once

#include <Eigen/Dense>
#include "EntityStates.h"

namespace UAV
{
class CommandInputHandler
{
    public:
        CommandInputHandler();

    protected:
        void processCommands();
        Eigen::Vector<double,6>& getCommandControlWrench() { return cmdControlWrench_; }
        EntityStates&            getCommandStates() { return cmdStates_; }

    private:
        Eigen::Vector<double,6> cmdControlWrench_{0,0,0,0,0,0};

        EntityStates cmdStates_{};
};
}

#endif