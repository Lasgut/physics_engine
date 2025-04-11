#include "Context.h"
#include <iostream>
#include "glad/gl.h"

Context::Context(Window& window) 
    : window_(window) 
{
    glContext_ = SDL_GL_CreateContext(window_.getSdlWindow());
    SDL_GL_SetSwapInterval(0); // disable vsync because of issues with AMD...
    
    if (!glContext_) {
        std::cerr << "ERROR: Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
    {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        exit(1);
    } 
    const char* glVersion = (const char*)glGetString(GL_VERSION);
    if (glVersion == nullptr) 
    {
        std::cerr << "ERROR: OpenGL context is not initialized or active!" << std::endl;
        exit(1);
    }
    std::cout << "OpenGL Version: " << glVersion << std::endl;
    
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

SDL_GLContext
Context::getGlContext() const
{
    return glContext_;
}
