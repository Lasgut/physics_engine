#define COMMAND_INPUT_HANDLER_H
#ifdef COMMAND_INPUT_HANDLER_H

#pragma once


class CommandInputHandler
{
    public:
        CommandInputHandler() = default;

    protected:
        void processCommand();
};

#endif