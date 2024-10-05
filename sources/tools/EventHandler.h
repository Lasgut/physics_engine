#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#pragma once
#include <SDL2/SDL.h>
#include "EventState.h"

class EventHandler
{
public:
    EventHandler(EventState& eventState);
    ~EventHandler();

    void update();

private:
    SDL_Event sdlEvent_;
    EventState& eventState_;

private:
    void quit();
    void mouseButton();
    void mouseMotion();
    void mouseMotionWhilePressed();

};

#endif