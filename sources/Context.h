#ifndef CONTEXT_H
#define CONTEXT_H

#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "Window.h"

class Context {
public:
    Context(Window& window);  
    ~Context();
     
    void swapBuffers();  

private:
    SDL_GLContext   glContext_;  
    Window&         window_;  
};

#endif
