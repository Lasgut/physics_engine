#include "Window.h"
#include <iostream>

Window::Window(const char* title, int width, int height) 
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } 
    else 
    {
        window_ = SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_UNDEFINED, 
                                   SDL_WINDOWPOS_UNDEFINED, 
                                   width, 
                                   height, 
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (window_ == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
}

Window::~Window() 
{
    SDL_DestroyWindow(window_);
    window_ = nullptr;
    SDL_Quit();
}

SDL_Window* 
Window::getSdlWindow() const 
{
    return window_;
}
