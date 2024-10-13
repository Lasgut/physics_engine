#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <glad/glad.h>
#include "ShaderHandler.h"

class Cube 
{
public:
    Cube();
    ~Cube();

    void draw(ShaderHandler& shader);

private:
    GLuint VAO_;
    GLuint VBO_;
};

#endif
