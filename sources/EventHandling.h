#ifndef EVENTHANDLING_H
#define EVENTHANDLING_H

#pragma once
#include <SDL2/SDL.h>
#include "EventState.h"

class EventHandling
{
public:
    EventHandling(EventState& eventState);
    ~EventHandling();

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