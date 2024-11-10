#include "Context.h"
#include <iostream>
#include "glad/gl.h"

Context::Context(Window& window) 
    : window_(window) 
{
    glContext_ = SDL_GL_CreateContext(window_.getSdlWindow());
    
    if (!glContext_) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    } 
    
    glViewport(0,0,1000,1000);
    glEnable(GL_DEPTH_TEST);
}

Context::~Context() 
{
    SDL_GL_DeleteContext(glContext_);
}

void Context::clear() 
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
