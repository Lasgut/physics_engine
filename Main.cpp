#include "Window.h"

int main(int argc, char* args[]) {
    Window myWindow("My SDL Window", 800, 600);

    // Main loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    return 0;
}
