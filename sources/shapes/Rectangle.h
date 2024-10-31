#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once
#include <glad/glad.h>
#include "ShaderHandler.h"

class Rectangle
{
public:
    Rectangle();
    ~Rectangle();

    void draw(ShaderHandler& shaderHandler);

private:
    GLuint VAO_;
    GLuint VBO_;

    float length_{1};
    float width_{1};
    float height_{1};

};

#endif