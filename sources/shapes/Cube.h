#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <glad/glad.h>

class Cube 
{
public:
    Cube();
    ~Cube();

    void draw();

private:
    GLuint VAO_;
    GLuint VBO_;
};

#endif
