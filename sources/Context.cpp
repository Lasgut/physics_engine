#include "Context.h"
#include <iostream>

Context::Context(Window& window) 
    : window_(window) 
{
    glContext_ = SDL_GL_CreateContext(window_.getSdlWindow());
    
    if (!glContext_) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit(1);
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(1);
    }

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

Context::~Context() 
{
    SDL_GL_DeleteContext(glContext_);
}

void Context::swapBuffers() 
{
    SDL_GL_SwapWindow(window_.getSdlWindow());
}
