#ifndef LINE_H
#define LINE_H

#pragma once
#include "ShaderHandler.h"
#include "Shape.h"
#include <glad/gl.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Line
    : public Shape
{
    public:
        Line();
        Line(float length, const glm::vec3& color);

        void draw(const ShaderHandler& shaderHandler, 
                const glm::vec3&     position,
                const glm::vec3&     orientation);

    private:
        void createVertices();

        float length_{1.0};
        glm::vec3 color_{0.5,0.5,0.5};
};

#endif // AXES_H
