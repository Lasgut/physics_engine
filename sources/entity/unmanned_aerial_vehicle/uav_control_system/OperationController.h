#define OPERATION_CONTROLLER_H
#ifdef OPERATION_CONTROLLER_H

#pragma once

#include "EntityStates.h"
#include "CommandInputHandler.h"
#include "StateController.h"

namespace UAV
{
class OperationController
    : public CommandInputHandler
    , public StateController
{
    public:
        OperationController() = default;

    protected:
        EntityStates computeDesiredStates();
};
}

#endif
