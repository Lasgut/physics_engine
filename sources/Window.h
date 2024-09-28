#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <SDL2/SDL.h>

class Window 
{    
public:
    Window(const char* title, int width, int height);
    ~Window();

    SDL_Window* getSdlWindow() const;

private:
    SDL_Window* window_;
};

#endif 
