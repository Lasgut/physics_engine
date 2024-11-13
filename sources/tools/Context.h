#ifndef CONTEXT_H
#define CONTEXT_H

#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "Window.h"

class Context {
public:
    Context(Window& window);  
    ~Context();
     
    void clear();  

    SDL_GLContext getGlContext() const;

private:
    SDL_GLContext   glContext_;  
    Window&         window_;  
};

#endif
