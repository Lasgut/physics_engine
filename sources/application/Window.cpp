#include "Window.h"
#include <iostream>

Window::Window(const char* title, int width, int height) 
    : width_(width)
    , height_(height)
    , sdlWindow_(nullptr)
{
    rightMouseButtonDown_ = false;
    leftMouseButtonDown_  = false;

    // Initialize SDL with OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } 
    else 
    {
        sdlWindow_ = SDL_CreateWindow(title,
                                      SDL_WINDOWPOS_UNDEFINED, 
                                      SDL_WINDOWPOS_UNDEFINED, 
                                      width, 
                                      height, 
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (sdlWindow_ == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
}


Window::~Window() 
{
    SDL_DestroyWindow(sdlWindow_);
    sdlWindow_ = nullptr;
    SDL_Quit();
}


void 
Window::swapBuffers()
{
    SDL_GL_SwapWindow(sdlWindow_);
}


SDL_Window*
Window::getSdlWindow() const 
{
    return sdlWindow_;
}


float 
Window::getWidth() const
{
    return width_;
}


float 
Window::getHeight() const
{
    return height_;
}
