#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <SDL2/SDL.h>

class Window 
{    
    public:
        Window(const char* title, int width, int height);
        ~Window();

        void swapBuffers();

        SDL_Window* getSdlWindow() const;
        float getWidth()  const;
        float getHeight() const;

    private:
        SDL_Window* sdlWindow_;
        SDL_Event   sdlEvent_;

        float width_;
        float height_;

        bool rightMouseButtonDown_;
        bool leftMouseButtonDown_;
};

#endif 
