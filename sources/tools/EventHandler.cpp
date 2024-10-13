#include "EventHandler.h"
#include "EventState.h"
#include <SDL2/SDL.h>
#include <iostream>

EventHandler::EventHandler(EventState& eventState)
    : eventState_(eventState)
{
    SDL_Event sdlEvent_;
}

EventHandler::~EventHandler()
{

}

void 
EventHandler::update()
{
    eventState_.mouse.xRel = 0;
    eventState_.mouse.yRel = 0;
    while (SDL_PollEvent(&sdlEvent_)) 
    {
        quit();
        mouseButton();
        mouseMotion();
        mouseMotionWhilePressed();
        ctrlButton();
    }
}

void 
EventHandler::quit()
{
    if (sdlEvent_.type == SDL_QUIT) 
    {
        eventState_.quit = true;
    }
}

void 
EventHandler::mouseButton()
{
    // Handle mouse button events
    if (sdlEvent_.type == SDL_MOUSEBUTTONDOWN) 
    {
        if (sdlEvent_.button.button == SDL_BUTTON_LEFT) 
        {
            eventState_.mouse.leftButtonDown = true;
        } 
        else if (sdlEvent_.button.button == SDL_BUTTON_RIGHT) 
        {
            eventState_.mouse.rightButtonDown = true;
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
EventHandler::mouseMotion()
{
    if (sdlEvent_.type == SDL_MOUSEMOTION) 
    {
        eventState_.mouse.x = sdlEvent_.motion.x;
        eventState_.mouse.y = sdlEvent_.motion.y;
    }
}

void 
EventHandler::mouseMotionWhilePressed()
{
    if (eventState_.mouse.leftButtonDown      &&
        std::abs(sdlEvent_.motion.xrel) < 100 &&
        std::abs(sdlEvent_.motion.yrel) < 100)
    {
        eventState_.mouse.xRel = sdlEvent_.motion.xrel;
        eventState_.mouse.yRel = sdlEvent_.motion.yrel;
    } 
}

void EventHandler::ctrlButton()
{
    if (sdlEvent_.type == SDL_KEYDOWN) 
    {
        if (sdlEvent_.key.keysym.sym == SDLK_LCTRL || sdlEvent_.key.keysym.sym == SDLK_RCTRL) 
        {
            eventState_.keyboard.ctrl = true; // Ctrl pressed
        }
    } 
    else if (sdlEvent_.type == SDL_KEYUP) 
    {
        if (sdlEvent_.key.keysym.sym == SDLK_LCTRL || sdlEvent_.key.keysym.sym == SDLK_RCTRL) 
        {
            eventState_.keyboard.ctrl = false; // Ctrl released
        }
    }
}