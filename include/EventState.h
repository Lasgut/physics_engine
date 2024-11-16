#ifndef EVENT_STATE_H
#define EVENT_STATE_H

#pragma once

struct MouseState 
{
    bool leftButtonDown  = false;
    bool rightButtonDown = false;
    float x              = 0;
    float y              = 0; 
    float xRel           = 0; 
    float yRel           = 0;  
    float wheelRel       = 0;
};

struct KeyboardState
{
    bool ctrl = false;
};

struct EventState 
{
    bool quit = false;
    MouseState mouse;
    KeyboardState keyboard;
};

#endif