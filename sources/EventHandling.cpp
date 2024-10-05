#include "EventHandling.h"
#include "EventState.h"
#include <SDL2/SDL.h>
#include <iostream>

EventHandling::EventHandling(EventState& eventState)
    : eventState_(eventState)
{
    SDL_Event sdlEvent_;
}

EventHandling::~EventHandling()
{

}

void 
EventHandling::update()
{
    while (SDL_PollEvent(&sdlEvent_)) 
    {
        quit();
        mouseButton();
        mouseMotion();
        mouseMotionWhilePressed();
    }
}

void 
EventHandling::quit()
{
    if (sdlEvent_.type == SDL_QUIT) 
    {
        eventState_.quit = true;
    }
}

void 
EventHandling::mouseButton()
{
    // Handle mouse button events
    if (sdlEvent_.type == SDL_MOUSEBUTTONDOWN) 
    {
        if (sdlEvent_.button.button == SDL_BUTTON_LEFT) 
        {
            eventState_.mouse.leftButtonDown = true;
            std::cout << "Left mouse button pressed" << std::endl;
        } 
        else if (sdlEvent_.button.button == SDL_BUTTON_RIGHT) 
        {
            eventState_.mouse.rightButtonDown = true;
            std::cout << "Right mouse button pressed" << std::endl;
        }
    }

    if (sdlEvent_.type == SDL_MOUSEBUTTONUP) 
    {
        if (sdlEvent_.button.button == SDL_BUTTON_LEFT) 
        {
            eventState_.mouse.leftButtonDown = false;
        } 
        else if (sdlEvent_.button.button == SDL_BUTTON_RIGHT) 
        {
            eventState_.mouse.rightButtonDown = false;
        }
    }
}

void 
EventHandling::mouseMotion()
{
    // Handle mouse motion events
    if (sdlEvent_.type == SDL_MOUSEMOTION) 
    {
        eventState_.mouse.x = sdlEvent_.motion.x; // Current X position
        eventState_.mouse.y = sdlEvent_.motion.y; // Current Y position
    }
}

void EventHandling::mouseMotionWhilePressed()
{
    if (eventState_.mouse.leftButtonDown)
    {
        eventState_.mouse.xRel = sdlEvent_.motion.xrel;
        eventState_.mouse.yRel = sdlEvent_.motion.yrel;
        std::cout << "mouse moving while pressed ("
                  << eventState_.mouse.xRel << ", "
                  << eventState_.mouse.yRel << ")"
                  << std::endl;
    }
    else
    {
        eventState_.mouse.xRel = 0;
        eventState_.mouse.yRel = 0;
    }
}
