#include "Window.h"
#include <iostream>

// Constructor
Window::Window(const char* title, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        // Create a window
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
}

// Destructor
Window::~Window() {
    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

// Get the SDL_Window pointer
SDL_Window* Window::getWindow() const {
    return window;
}
