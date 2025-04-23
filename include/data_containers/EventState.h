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
    public:
        static EventState& getInstance()
        {
            static EventState instance;
            return instance;
        };

        bool          quit = false;
        MouseState    mouse;
        KeyboardState keyboard;

    private:
        EventState()                             = default;
        ~EventState()                            = default;
        EventState(const EventState&)            = delete;
        EventState& operator=(const EventState&) = delete;
        EventState(EventState&&)                 = delete;
        EventState& operator=(EventState&&)      = delete;
};

#endif