#ifndef EVENT_STATE_H
#define EVENT_STATE_H

#pragma once

struct MouseState 
{
    bool leftButtonDown = false;
    bool rightButtonDown = false;
    int x = 0;  // Current mouse x position
    int y = 0;  // Current mouse y position
    int xRel = 0;  // Relative mouse movement in x
    int yRel = 0;  // Relative mouse movement in y
};

struct EventState 
{
    bool quit = false;
    MouseState mouse;
    // You can expand this with keyboard states, etc.
};

#endif // EVENT_STATE_H