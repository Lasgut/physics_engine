#include "Window.h"
#include "Context.h"
#include "Axes.h"
#include "Camera.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char* argv[]) 
{
    // Create window and context
    Window window("Physics Engine", 1200, 1200);
    Context context(window);

    // Initialize camera
    Camera camera;

    bool isRunning = true;
    SDL_Event event;

    // Main loop
    while (isRunning) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                isRunning = false;
            }

            // Handle mouse motion to adjust camera
            if (event.type == SDL_MOUSEMOTION) {
                float xoffset = event.motion.xrel;  // Change in x
                float yoffset = event.motion.yrel;  // Change in y
                camera.processMouseMovement(xoffset, yoffset);
            }

            // Clear the screen and depth buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            // Set up the projection matrix
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0, 1200.0 / 1200.0, 0.1, 100.0);

            // Set the view matrix from the camera
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glm::mat4 view = camera.getViewMatrix();
            glLoadMatrixf(&view[0][0]); // Load the view matrix

            // Draw the 3D axes
            Axes axes;

            // Swap the buffers to display the rendered image
            context.swapBuffers();

            // Delay for ~60 FPS
            SDL_Delay(16);
        }
    }

    return 0;
}
