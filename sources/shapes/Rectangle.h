#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once
#include <glad/glad.h>
#include "ShaderHandler.h"
#include "Shape.h"
#include <vector>

class Rectangle
    : public Shape
{
public:
    Rectangle();
    Rectangle(float length, float width, float height);

    void draw(const ShaderHandler& shaderHandler, 
              const glm::vec3&     position,
              const glm::vec3&     orientation);

private:
    std::vector<float> createVertices();

    float length_{1};
    float width_{1};
    float height_{1};

};

#endif