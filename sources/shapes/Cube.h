#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <glad/gl.h>
#include <Shape.h>
#include "ShaderHandler.h"

class Cube 
    : public Shape
{
public:
    Cube();
    Cube(float length, float width, float height);

    void draw(const ShaderHandler& shaderHandler, 
              const glm::vec3&     position,
              const glm::vec3&     orientation);

private:
    std::vector<float> createVertices();

    float length_{0.1};
    float width_{0.1};
    float height_{0.1};        
};

#endif
