#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class Window {
public:
    // Constructor
    Window(const char* title, int width, int height);
    
    // Destructor
    ~Window();

    // Get the SDL_Window pointer
    SDL_Window* getWindow() const;

private:
    SDL_Window* window;  // SDL Window pointer
};

#endif // WINDOW_H
