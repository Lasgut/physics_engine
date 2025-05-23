#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#pragma once
#include <SDL2/SDL.h>
#include "EventState.h"

class EventHandler
{
    public:
        EventHandler();

        void update();

    private:
        SDL_Event sdlEvent_;
        EventState& eventState_;

    private:
        void quit();

        void mouseEvents();
        void mouseButton();
        void mouseMotion();
        void mouseMotionWhilePressed();
        void mouseWheel();

        void keyboardEvents();
        void ctrlButton();
        void arrowButtons();
};

#endif